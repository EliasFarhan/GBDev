"""Deduplicate exact-duplicate 16-byte tiles in a GBDK sprite .s file that
already has a tilemap indirection (tiledata symbol + tilemap symbol).

Unlike merge_gbs.py (which resets the tilemap to identity and therefore only
works on full-screen images), this keeps the existing frame->tile mapping and
remaps it through the dedup table.

Usage:
    python3 tools/dedup_sprite_tiles.py data/peanut.s tile_peanut tilemap_peanut

Rewrites the file in place. Remember to update the matching *_SPR_LEN constant
in src/game_screen.h with the new unique-tile count printed on stdout.
"""
import re
import sys


def main(path, tiles_sym, map_sym):
    raw = open(path, newline='').read()
    lines = raw.splitlines()
    tiles_bytes, map_bytes = [], []
    cur = None
    for ln in lines:
        s = ln.strip()
        if s.startswith('_%s:' % tiles_sym):
            cur = 'tiles'
            continue
        if s.startswith('_%s:' % map_sym):
            cur = 'map'
            continue
        if s.lower().startswith('.db') and cur:
            vals = [int(b, 16) for b in re.findall(r'0[xX]([0-9A-Fa-f]{2})', s)]
            (tiles_bytes if cur == 'tiles' else map_bytes).extend(vals)

    area = next((ln.strip() for ln in lines if ln.strip().startswith('.area')), '.area _CODE_1')
    n = len(tiles_bytes) // 16
    tiles = [tuple(tiles_bytes[i * 16:(i + 1) * 16]) for i in range(n)]

    uniq, remap = [], {}
    for t in tiles:
        if t not in remap:
            remap[t] = len(uniq)
            uniq.append(t)
    old_to_new = [remap[t] for t in tiles]
    new_map = [old_to_new[m] for m in map_bytes]
    print('%s: %d tiles -> %d unique (saves %d bytes)'
          % (path, n, len(uniq), (n - len(uniq)) * 16))

    def db_lines(vals, per):
        return ['.db ' + ','.join('0x%02X' % v for v in vals[i:i + per])
                for i in range(0, len(vals), per)]

    out = [area, '', '.globl _%s' % tiles_sym, '.dw _%s' % tiles_sym, '',
           '_%s:' % tiles_sym]
    out += db_lines([b for t in uniq for b in t], 8)
    out += ['', '.globl _%s' % map_sym, '.dw _%s' % map_sym, '', '_%s:' % map_sym]
    out += db_lines(new_map, 16)
    open(path, 'w').write('\n'.join(out) + '\n')


if __name__ == '__main__':
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    main(sys.argv[1], sys.argv[2], sys.argv[3])

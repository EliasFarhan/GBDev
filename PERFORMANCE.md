---
title: Performance Guide — SRJailbreak (GBDK-2020)
tags: [gbdev, srjailbreak, plan, performance, rom-size, banking]
status: active
updated: 2026-07-08
related:
  - "[[MIGRATION_PLAN]]"
  - "[[WARNINGS_FIX_PLAN]]"
---

# PERFORMANCE.md — Game Boy Performance Guide for SRJailbreak

This document covers performance considerations, optimizations, and best practices for this GBDK-2020 Game Boy project.

> [!success] Primary goal ACHIEVED — 2026-07-08
> The ROM has been shrunk from **256 KB MBC1+RAM+BATT** to **64 KB MBC5, 4 banks, no RAM** (header bytes `19 01 00`, ROM is exactly 65,536 bytes). Four optimizations landed in this pass: `--opt-code-size`, collision-iteration micro-opts, batched tilemap loading, and the full 8→4 bank consolidation. All verified by clean `make` + `.map`/header inspection. **Still needs runtime testing on an emulator** (a banking regression builds cleanly but only shows at runtime) — see the per-section notes below.

> [!success] Historical note
> Everything below was written as forward-looking. The four items marked ✅ IMPLEMENTED have now shipped; the rest (sprite flipping, level-handler consolidation, tile dedup, music-driver swap, RAM packing) remain open.

## Table of Contents

1. [ROM & RAM Size Analysis](#rom--ram-size-analysis)
2. [ROM Size Optimization Goal](#rom-size-optimization-goal)
3. [Current Optimizations](#current-optimizations)
4. [Potential Improvements](#potential-improvements)
5. [GBDK-2020 Compiler Optimizations](#gbdk-2020-compiler-optimizations)
6. [CPU & Memory Considerations](#cpu--memory-considerations)
7. [Sprite & Graphics Performance](#sprite--graphics-performance)
8. [Collision Detection](#collision-detection)
9. [Sound Performance](#sound-performance)
10. [Banking Best Practices](#banking-best-practices)
11. [Profiling & Debugging](#profiling--debugging)

---

## ROM & RAM Size Analysis

### Game Boy Cartridge Types Reference

#### ROM-Only (No MBC)

| Type Code | ROM Size | RAM Size | Notes |
|-----------|----------|----------|-------|
| 0x00 | 32 KB (2 banks) | None | Simplest, no mapper needed |

#### MBC1 (Memory Bank Controller 1)

| Type Code | ROM Size | RAM Size | Notes |
|-----------|----------|----------|-------|
| 0x01 | Up to 2 MB | None | ROM banking only |
| 0x02 | Up to 2 MB | Up to 32 KB | With RAM |
| 0x03 | Up to 2 MB | Up to 32 KB | With RAM + Battery (save) |

**MBC1 ROM sizes:**

| Banks | Size | Hex Header Value |
|-------|------|------------------|
| 2 | 32 KB | 0x00 |
| 4 | 64 KB | 0x01 |
| 8 | 128 KB | 0x02 |
| 16 | 256 KB | 0x03 |
| 32 | 512 KB | 0x04 |
| 64 | 1 MB | 0x05 |
| 128 | 2 MB | 0x06 |

**MBC1 RAM sizes:**

| Banks | Size | Hex Header Value |
|-------|------|------------------|
| 0 | None | 0x00 |
| 1 | 8 KB | 0x02 |
| 4 | 32 KB | 0x03 |

#### MBC2

| Type Code | ROM Size | RAM Size | Notes |
|-----------|----------|----------|-------|
| 0x05 | Up to 256 KB | 512 x 4 bits | Built-in RAM (256 bytes usable) |
| 0x06 | Up to 256 KB | 512 x 4 bits | With Battery |

#### MBC3 (with RTC support)

| Type Code | ROM Size | RAM Size | Notes |
|-----------|----------|----------|-------|
| 0x0F | Up to 2 MB | None | Timer only |
| 0x10 | Up to 2 MB | Up to 32 KB | Timer + RAM + Battery |
| 0x11 | Up to 2 MB | None | ROM only |
| 0x12 | Up to 2 MB | Up to 32 KB | With RAM |
| 0x13 | Up to 2 MB | Up to 32 KB | With RAM + Battery |

#### MBC5 (most common for later games)

| Type Code | ROM Size | RAM Size | Notes |
|-----------|----------|----------|-------|
| 0x19 | Up to 8 MB | None | ROM only |
| 0x1A | Up to 8 MB | Up to 128 KB | With RAM |
| 0x1B | Up to 8 MB | Up to 128 KB | With RAM + Battery |
| 0x1C | Up to 8 MB | None | With Rumble |
| 0x1D | Up to 8 MB | Up to 128 KB | Rumble + RAM |
| 0x1E | Up to 8 MB | Up to 128 KB | Rumble + RAM + Battery |

**MBC5 ROM sizes:**

| Banks | Size | Hex Header Value |
|-------|------|------------------|
| 2 | 32 KB | 0x00 |
| 4 | 64 KB | 0x01 |
| 8 | 128 KB | 0x02 |
| 16 | 256 KB | 0x03 |
| 32 | 512 KB | 0x04 |
| 64 | 1 MB | 0x05 |
| 128 | 2 MB | 0x06 |
| 256 | 4 MB | 0x07 |
| 512 | 8 MB | 0x08 |

**MBC5 RAM sizes:**

| Banks | Size | Hex Header Value |
|-------|------|------------------|
| 0 | None | 0x00 |
| 1 | 8 KB | 0x02 |
| 4 | 32 KB | 0x03 |
| 16 | 128 KB | 0x04 |
| 8 | 64 KB | 0x05 |

#### Other MBCs (less common)

| Type Code | Name | ROM Size | RAM Size | Notes |
|-----------|------|----------|----------|-------|
| 0x0B-0x0D | MMM01 | Varies | Varies | Multi-cart mapper |
| 0x20 | MBC6 | Up to 2 MB | Up to 32 KB | Flash memory support |
| 0x22 | MBC7 | Up to 2 MB | 256 bytes | Accelerometer + EEPROM |
| 0xFC | Pocket Camera | 1 MB | 128 KB | GB Camera |
| 0xFD | Bandai TAMA5 | 512 KB | 32 bytes | Tamagotchi games |
| 0xFE | HuC3 | Up to 2 MB | 128 KB | Hudson mapper |
| 0xFF | HuC1 | Up to 2 MB | 32 KB | Hudson mapper + IR |

### Current Project Configuration

```
ROM Type: MBC5 (0x19)
ROM Size: 64 KB (4 banks, header 0x01)
RAM Size: None (0x00)
```
Confirmed live from `SRJailbreak.gb` header bytes 0x147-0x149 on 2026-07-08: cart type `0x19`, ROM size code `0x01`, RAM size code `0x00`. ROM file is exactly 65,536 bytes.

> [!info]- Previous configuration (before the 2026-07-08 consolidation)
> ```
> ROM Type: MBC1+RAM+BATTERY (0x03)
> ROM Size: 256 KB (16 banks, header 0x03)
> RAM Size: 8 KB (1 bank, header 0x02)
> ```
> Set in the Makefile via `-Wl-yt3 -Wl-yo16 -Wl-ya1`; now `-Wl-yt0x19 -Wl-yo4 -Wl-ya0`.

### Target Configuration — MBC5, 64 KB {#target-configuration-mbc5}

```
ROM Type: MBC5 (0x19)
ROM Size: 64 KB (4 banks, header 0x01)
RAM Size: None (0x00)
```

**Makefile change:**
```makefile
# MBC5, 64KB ROM (4 banks), no RAM
LCCFLAGS += -Wl-yt0x19 -Wl-yo4 -Wl-ya0
```

**Fallback if 64 KB proves too tight after optimization:**
```makefile
# MBC5, 128KB ROM (8 banks), no RAM
LCCFLAGS += -Wl-yt0x19 -Wl-yo8 -Wl-ya0
```

**Why MBC5 over sticking with MBC1:**

| Pros | Cons |
|------|------|
| Best compatibility with modern flash chips | Slightly more complex PCB |
| Widely supported by reproduction PCBs | MBC5 chip needed |
| No bank switching bugs (unlike MBC1) | |
| Supports large ROM and RAM | |
| Industry standard for late GB/GBC games | |

> [!info]- Alternatives considered, and rejected
> - **No MBC (32 KB):** simplest/cheapest PCB, but would need cutting ~5 KB from the game and drops save capability. Not recommended.
> - **MBC1 (32 KB–2 MB):** cheaper donor carts, but has bank-switching quirks above 1 MB and worse flash-chip compatibility than MBC5. Not recommended for new production.
> - **MBC2/MBC3/MBC6/MBC7/HuC1/HuC3:** avoid for physical carts — weird RAM addressing, RTC/battery complexity, rare/proprietary chips.

> [!info]- Physical cartridge production reference — PCBs, flash chips, cost
> **PCB/cartridge sources:** InsideGadgets (new PCBs, various sizes) · Catskull Electronics (quality reproduction boards) · HDR/Hand Held Legend (flash carts) · Ferrante Crafts (custom PCBs) · AliExpress (budget reproduction boards, variable quality)
>
> **Flash chip compatibility:**
>
> | Flash Chip | Size | MBC Compatibility | Notes |
> |------------|------|-------------------|-------|
> | 29F032 | 4 MB | MBC5 | Common, cheap |
> | 29F016 | 2 MB | MBC1, MBC5 | Good availability |
> | 29F008 | 1 MB | MBC1, MBC5 | |
> | 29F040 | 512 KB | MBC1, MBC5 | |
> | 29F020 | 256 KB | MBC1, MBC5 | Good for small games |
> | 29F010 | 128 KB | MBC1, MBC5 | |
> | 27C512 | 64 KB | No MBC, MBC1, MBC5 | EPROM (needs UV eraser) |
> | 27C256 | 32 KB | No MBC | EPROM, simplest option |
>
> **Cost comparison (MBC5 options):**
>
> | Configuration | PCB Cost | Components | Total (per unit) |
> |---------------|----------|------------|------------------|
> | **MBC5, 64 KB** ★ | $5-10 | $3-6 | **$8-15** |
> | MBC5, 128 KB | $5-10 | $4-8 | **$9-18** |
> | MBC5, 256 KB | $5-10 | $5-10 | **$10-20** |
>
> Prices vary by quantity and source; shell/case adds $2-5. **Target: MBC5 + 64 KB ≈ $8-15/cartridge**, no save RAM needed.
>
> **GBDK-2020 header flags reference:**
>
> | Flag | Meaning |
> |------|---------|
> | `-Wl-yt0xNN` | Cartridge type (MBC) |
> | `-Wl-yoN` | ROM size (N = number of banks) |
> | `-Wl-yaN` | RAM size (0=none, 2=8KB, 3=32KB) |

### Detailed Bank & Asset Breakdown (historical — pre-consolidation 256 KB build)

> [!info]- Bank usage by linker section — click to expand
> | Bank | Section | Size (bytes) | Contents |
> |------|---------|--------------|----------|
> | 0 | _CODE | 1,576 | Main loop, sound, GBT stubs |
> | 0 | _HOME | 6,520 | `NONBANKED` functions (game_screen, collision, etc.) |
> | 0 | _INITIALIZER | 713 | Initialized data |
> | 0 | Headers | ~350 | System headers |
> | **0 Total** | | **9,159** | |
> | 2 | _CODE_2 | 1,516 | Music data (song0-3, victory) |
> | 3 | _CODE_3 | 4,264 | kwakwa_logo, titlescreen2 graphics |
> | 4 | _CODE_4 | 1,649 | GBT player bank 1 |
> | 5 | _CODE_5 | 4,877 | Sprites (peanut, guard, seagull, etc.) |
> | 6 | _CODE_6 | 10,167 | Physics code, level tilemaps |
> | 7 | _CODE_7 | 2,443 | Doggy sprites, player sprite management |
> | 8 | _CODE_8 | 2,674 | Credits, staffroll graphics |
>
> Re-verified against `SRJailbreak.map` 2026-07-08 — every byte count above matched exactly.

> [!info]- Detailed asset sizes — click to expand
> **Graphics assets (~12,765 bytes)**
>
> | Asset | Size | Notes |
> |-------|------|-------|
> | tile_peanut | 1,730 bytes | 108 animation frames (player) |
> | tilemap_peanut | 122 bytes | Frame index mapping |
> | tile_guard | 770 bytes | 48 frames (enemy) |
> | tile_seagull | 258 bytes | 16 frames (flying enemy) |
> | tilemap_seagull | 20 bytes | Frame mapping |
> | tile_environment | 306 bytes | 9 frames |
> | tile_background | 130 bytes | Background tiles |
> | tile_whale_poster | 770 bytes | In-game decoration |
> | tile_white_fur | 18 bytes | Bonus character |
> | tile_white_background | 514 bytes | |
> | press_start | 237 bytes | UI element |
> | titlescreen2 | 3,420 bytes | Title screen (merged) |
> | kwakwa_logo | 2,124 bytes | Intro logo (merged) |
> | staffroll | 2,346 bytes | Credits screen (merged) |
>
> **Level data (~6,240 bytes)**
>
> | Asset | Size | Notes |
> |-------|------|-------|
> | 15 level tilemaps | 5,400 bytes | 360 bytes each (20×18 tiles) |
> | Collision boxes | ~300 bytes | ~5 boxes per level average |
> | Entity metadata | ~540 bytes | Keys, locks, enemies, doggies |
>
> **Music & sound (~3,745 bytes)**
>
> | Asset | Size | Notes |
> |-------|------|-------|
> | GBT Player (bank 0) | 254 bytes | Music driver stub |
> | GBT Player (bank 4) | 1,649 bytes | Full music engine |
> | song0 | 298 bytes | Gameplay music |
> | song1 | 313 bytes | |
> | song2 | 314 bytes | |
> | song3 | 323 bytes | |
> | victory_song | 268 bytes | |
> | title_song | 326 bytes | Title screen music |
>
> **Game code (~15,557 bytes)**
>
> | Module | Size | Location |
> |--------|------|----------|
> | game_screen.c | ~4,500 bytes | Bank 0 (NONBANKED) |
> | physics.c | ~3,600 bytes | Bank 6 |
> | manage_doggy_sprites | ~1,750 bytes | Bank 7 |
> | GBDK runtime | ~1,800 bytes | Bank 0 |
> | Level handlers (1-6) | ~1,200 bytes | Bank 6 |
> | Level handlers (7-13) | ~800 bytes | Bank 6 |
> | sound.c | ~440 bytes | Bank 0 |
> | title_screen.c | ~400 bytes | Bank 0 |
> | credits.c | ~200 bytes | Bank 0 |
> | kwakwa_screen.c | ~100 bytes | Bank 0 |

> [!info]- RAM usage — click to expand
> | Section | Address | Size | Contents |
> |---------|---------|------|----------|
> | Shadow OAM | 0xC000 | 160 bytes | Sprite attribute buffer |
> | _DATA | 0xC0A0 | 172 bytes | Runtime variables |
> | _INITIALIZED | 0xC14C | 713 bytes | Level data, player, enemies |
> | _HRAM | 0xFF80 | 19 bytes | Fast-access variables |
> | Stack | ~0xDFxx | ~256 bytes | Call stack |
> | **TOTAL** | | **1,320 bytes** | **16.1% of 8KB WRAM** |

---

## ROM Size Optimization Goal

The 256 KB MBC1 ROM was heavily underutilized (14%). Goal achieved: everything now fits the smallest practical MBC5 configuration — see [[#Target Configuration — MBC5, 64 KB|Target Configuration]] above for the exact header/Makefile values.

| ROM Size | Banks | MBC5 Type | Feasibility |
|----------|-------|-----------|-------------|
| **64 KB** | 4 | MBC5 (0x19) | ✅ **Shipped** (2026-07-08) |
| 128 KB | 8 | MBC5 (0x19) | Fallback if a bank ever overflows 16 KB |
| 256 KB | 16 | MBC1 (0x03) | Old size (wasteful) |

### Space Budget for 64 KB Target

| Bank | Budget | Planned Contents |
|------|--------|------------------|
| 0 (fixed) | 16,384 bytes | Core code, `NONBANKED` functions, runtime |
| 1 | 16,384 bytes | All sprites, UI graphics |
| 2 | 16,384 bytes | Level tilemaps, physics, level handlers |
| 3 | 16,384 bytes | Full-screen graphics, music, credits |
| **Total** | **65,536 bytes** | |

Current data (~37 KB) leaves ~28 KB headroom in a 64 KB ROM.

### Graphics Optimization Strategies

> [!todo] 1. Reduce player animation frames
> Current: 108 frames (1,730 bytes). Many left/right pairs may be redundant if mirrored via the OAM flip flag instead of stored twice:
> ```c
> set_sprite_prop(sprite_id, S_FLIPX);  // Mirror sprite horizontally
> ```
> **Potential savings:** 40–50% of player sprites (~700–850 bytes)

> [!todo] 2. Merge duplicate tiles in sprites
> `merge_gbs.py` is already used for full-screen graphics (`titlescreen2`, `kwakwa_logo`, `staffroll`). Apply it to sprite sheets too:
> ```bash
> python tools/merge_gbs.py data/peanut.s > data/peanut_merge.s
> ```

> [!todo] 3. Remove unused full-screen graphics
> Audit for redundant screens (e.g. overlapping title/credits backgrounds) and consolidate.

> [!todo] 4. Use 1bpp tiles where possible
> For simple graphics (text, UI), 1bpp halves storage vs. 2bpp (8 vs 16 bytes per 8×8 tile).

> [!todo] 5. Tile deduplication across levels
> Levels likely share common tiles (floors, walls). Replace 15 separate 360-byte tilemaps with one shared tileset + 15 smaller index maps.
> **Potential savings:** 20–30% (~1,000–1,500 bytes)

### Code Size Optimization

> [!success] 1. Use `--opt-code-size` — ✅ IMPLEMENTED (2026-07-08)
> ```makefile
> CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j -Wf--opt-code-size
> ```
> **Gotcha:** a bare `--opt-code-size` on the lcc line is *silently swallowed* — lcc does not forward it to sdcc. It must be passed as **`-Wf--opt-code-size`** (verify with `lcc ... -v` that the sdcc invocation actually includes `--opt-code-size`).
> **Measured effect on this codebase: essentially neutral** (`_HOME` +11 B, banked code −7 B). SDCC's default already optimizes this code well; kept for the size-first posture. Side effect: the optimizer now emits `warning 110` at the two pre-existing `player.timer & 1U == 0U` precedence bugs in `physics.c` (harmless, condition was always-true before too).

> [!todo] 2. Eliminate redundant level handler functions
> Current: separate `manage_physics_lvl1()`…`manage_physics_lvl15()` and `reset_lvl1()`…`reset_lvl15()`. Consolidate into a data-driven approach:
> ```c
> // Instead of 15 separate functions, one parameterized function
> // indexing into per-level data tables:
> void manage_physics_level(UBYTE level_id) { ... }
> ```
> **Potential savings:** 2,000–4,000 bytes

> [!todo] 3. Lookup tables instead of switch statements
> ```c
> // SMALLER: function-pointer table instead of a switch
> typedef void (*StateHandler)(void);
> const StateHandler handlers[] = { handle_idle, handle_walk, ... };
> handlers[state]();
> ```

> [!todo] 4. Remove debug code
> Confirm no `printf`/logging/debug-only code remains in release builds.

> [!todo] 5. Inline trivial functions
> ```c
> // Instead of a call/return for a one-liner:
> #define SET_FLAG(f) (player.booleanState |= (f))
> ```

### Music & Sound Optimization {#music-sound-optimization}

> [!todo] Options
> - Replace GBT Player (~1,900 bytes across banks 0/4) with **hUGEDriver** for a smaller footprint. (Also flagged from the migration side — see [[MIGRATION_PLAN#Still Open]].)
> - Reduce song count / reuse patterns if songs are musically similar.
> - GBT's pattern format is already compact, but further pattern reuse can shrink it more.

### Banking Consolidation Strategy — ✅ IMPLEMENTED (2026-07-08)

**Was: 8 banks (256 KB)** → **Now: 4 banks (64 KB MBC5)**. Live `.map` sizes after consolidation:

| New bank | Size Used | Contents | Merged from (old banks) |
|----------|-----------|----------|--------------------------|
| 0 (fixed) | 8,634 bytes | `_CODE` 1,486 + `_HOME` 6,435 + `_INITIALIZER` 713 (main, box_collision, sound, gbt_player, all `NONBANKED`) | 0 |
| 1 | 4,877 bytes | All sprite/UI data (peanut, guard, seagull, environment, background, white_fur, whale_poster, press_start) | 5 |
| 2 | 12,753 bytes | physics, levels/*, data/map/* tilemaps, **game_screen.o** | 6 + 7 (game_screen) |
| 3 | 10,103 bytes | kwakwa_logo, titlescreen2, music_output, gbt_player_bank1, staffroll, title_screen_music, credits/kwakwa/title code | 2, 3, 4, 8 + 7 (screens) |

All four banks are under the 16,384-byte limit; total ROM = 65,536 bytes.

**Why `game_screen.o` → bank 2:** its only *banked* function `manage_doggy_sprites` reads `levels[currentLvl]->doggy` level data; co-locating the code with that data (both bank 2) removes the previous non-obvious cross-bank read.

> [!success]- How it was done — click to expand
> - **Makefile header:** `-Wl-yt0x19 -Wl-yo4 -Wl-ya0` (MBC5 / 4 banks / no RAM).
> - **`-Wf-bo#` remap:** bo5→bo1 (sprites), bo6→bo2 (levels/maps/physics), bo7→bo2 (game_screen) / bo3 (credits, kwakwa, title_screen), bo2/bo4/bo8→bo3 (music, gbt bank1, staffroll+title music).
> - **`.s` files need `.area` edits, not `-Wf-bo`:** hand-written/merged assembly (`data/peanut.s` etc., `gbt_player_bank1.s`, `staffroll_merge.s`) hardcode `.area _CODE_N`, which the `-Wf-bo` flag does **not** override. Their area directives were edited directly (sprites `_CODE_5`→`_CODE_1`, staffroll `_CODE_8`→`_CODE_3`, gbt_player_bank1 `_CODE_4`→`_CODE_3`). Note these files use CRLF line endings.
> - **Runtime switches:** every `SWITCH_ROM_MBC1(n)` → `SWITCH_ROM_MBC5(m)` with renumbered banks (5→1, 6→2, 7→2, 8→3, 3→3, 0→0). This collapses the old per-frame 6↔7 churn (physics + doggy + player sprites now all bank 2).
> - **RAM removed:** audited for `0xA000–0xBFFF` (SRAM) access — none — then removed all `ENABLE_RAM_MBC1` calls.
> - **GBT music bank (two separate fixes):**
>   1. `gbt_play()` takes the *song data* bank as arg 2 — updated song/victory `0x02`→`0x03` and title `0x08`→`0x03` to follow the music data's new bank.
>   2. **⚠️ Hidden hardcode:** `src/gbt_player.s` hardcodes the *engine-code* bank as `ld a,#0x04` in **three** places (lines ~337/364/491, each right before `ld (#0x2000),a` and a `call gbt_update[_effects]_bank1`). That `0x04` is the bank where `gbt_player_bank1.o` was linked. Moving that code to bank 3 (`.area _CODE_3`) requires changing all three to `ld a,#0x03`, otherwise the engine switches to an empty bank 4 and calls garbage → **all music silently dies** while the game keeps running. This is exactly the kind of runtime-only regression that a clean build + `.map` will not catch.
> - **Makefile fix:** `levels/level10.c` / `level13.c` were listed as `.c` (bypassing the bank rule) — changed to `.o`.

> [!todo] Remaining banking follow-ups (not required for 64 KB)
> - [ ] Dead map data for levels 7-9, 11, 12, 14, 15 (unused `data/map/*_map.o`) still occupies bank 2 — removing it would free ~2.5 KB.
> - [ ] Consolidate the per-level handler functions (`manage_physics_lvlN`/`reset_lvlN`) — separate ROM-size task.

### RAM Optimization

Current RAM usage is healthy (16.1%), but can be reduced:

> [!todo] Options
> 1. **Reuse buffers** — level-specific data (collision boxes, enemies) can share memory via a union:
>    ```c
>    union LevelEntities {
>        struct { SEAGULL seagulls[4]; } flying_level;
>        struct { DOGGY doggies[2]; } guard_level;
>    };
>    ```
> 2. **Pack related flags into bitfields** instead of separate `UBYTE` flags:
>    ```c
>    UBYTE contactFlags;  // bit 0: ground, bit 1: front, bit 2: wall
>    ```
> 3. **Smaller data types** — confirm no `int` (16-bit) where `UBYTE` (8-bit) suffices.
> 4. **Stack usage** — avoid large local arrays; use global buffers instead.

---

## ROM Size Reduction Checklist

- [x] Apply `--opt-code-size` compiler flag *(as `-Wf--opt-code-size`; effect ~neutral)*
- [ ] Consolidate level handler functions into a data-driven approach
- [ ] Use sprite flipping (`S_FLIPX`) instead of storing mirrored frames
- [ ] Run `merge_gbs.py` on all sprite sheets
- [ ] Remove unused graphics and code
- [x] Consolidate from 8 banks to 4 banks *(now MBC5, 64 KB)*
- [ ] Replace large switch statements with lookup tables
- [ ] Remove all debug/development code
- [ ] Consider a smaller music driver (hUGEDriver)
- [ ] Use shared tilesets across levels
- [ ] Ensure no redundant full-screen graphics

### Expected Results

| Optimization | Estimated Savings |
|--------------|-------------------|
| Sprite flipping | 700-850 bytes |
| Level handler consolidation | 2,000-4,000 bytes |
| `--opt-code-size` | 500-1,000 bytes |
| Tile deduplication | 1,000-1,500 bytes |
| Music driver swap | 500-800 bytes |
| **Total potential** | **4,700-8,150 bytes** |

After optimization, the ROM should fit comfortably in **64 KB** with room to spare.

---

## Current Optimizations

> [!success]- Already implemented — click to expand
> The project already implements several good performance practices:
>
> **Data types (`game_screen.h`)**
> - 8-bit types throughout: all position, state, and counter variables use `UBYTE`/`BYTE`
> - The Z80-derived SM83 CPU is 8-bit; 16-bit operations require multiple instructions
> - Structs are compact (e.g. `Box` is 4 bytes, `PLAYER` is ~21 bytes)
>
> **Bitwise state flags (`game_screen.h:7-13`)**
> ```c
> #define HASJUMP        0x01
> #define TRANSITIONNING 0x04
> #define HASKEY         0x08
> #define HASGAMEOVER    0x10
> #define HASVICTORY     0x20
> #define WORLD_SWITCH   0x40
> ```
> Six boolean states packed into a single `UBYTE`, using fast bitwise ops instead of separate booleans.
>
> **`NONBANKED` critical functions** — `checkCollision()`, `game_screen()`, and `switch_to_level()` are marked `NONBANKED` and stay in the fixed bank 0, avoiding bank-switch overhead.
>
> **Early-exit collision detection (`box_collision.c:12-19`)**
> ```c
> UBYTE checkCollision(void) NONBANKED
> {
>     if(box2->x >= box1->x+box1->w) return 0;
>     if(box2->x+box2->w <= box1->x) return 0;
>     if(box2->y <= box1->y-box1->h) return 0;
>     if(box2->y-box2->h >= box1->y) return 0;
>     return 1;
> }
> ```
> Separating-axis test with early returns — most non-colliding boxes exit after 1-2 comparisons.
>
> **Frame-locked main loop (`game_screen.c:939-982`)** — uses `vsync()` for consistent 60 FPS timing, with conditional physics updates skipped during state transitions.
>
> **Global loop counter reuse** — a single `UBYTE i` is reused across all loops, avoiding stack allocation overhead.

---

## Potential Improvements

### 1. Compiler optimization flags

**Current Makefile lacks optimization flags.** Add these to the `CC` line:

```makefile
# Recommended
CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j --max-allocs-per-node 50000

# Or for aggressive optimization:
CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j --max-allocs-per-node 100000 --opt-code-speed
```

| Flag | Effect |
|------|--------|
| `--max-allocs-per-node N` | Increase register allocation attempts (default ~3000, try 50000+) |
| `--opt-code-speed` | Optimize for speed over size |
| `--opt-code-size` | Optimize for size (useful if ROM is tight) |
| `--peep-return` | Enable return peephole optimization |
| `--allow-unsafe-read` | Allow potentially unsafe optimizations |

### 2. Replace division/modulo with bitwise operations

Division and modulo are extremely expensive on Game Boy (~200+ cycles):

```c
// SLOW
UBYTE result = value / 8;
UBYTE remainder = value % 8;

// FAST (for powers of 2)
UBYTE result = value >> 3;
UBYTE remainder = value & 0x07;
```

> [!todo] Action item
> Check `physics.c` and `game_screen.c` for any remaining `/` or `%` operators. *(Not yet audited as part of this pass — [[WARNINGS_FIX_PLAN]] did not touch this.)*

### 3. Reduce collision box iterations — ✅ PARTIALLY IMPLEMENTED (2026-07-08, micro-opts only)

Physics functions iterated through **all** collision boxes every frame:
```c
for(i = 0U; i != levels[currentLvl]->boxes_length; i++)
```

**Done (behavior-preserving micro-opts):** in all 8 loops in `physics.c`, `boxes_length` (a 16-bit `const size_t`) is now cached into a `UBYTE n` local so the bound check is an 8-bit compare against the `UBYTE i` counter. Safe early `break`s were added in `manage_static_physics2` and `manage_climbwalk2` (exit once ground+front contacts are resolved or inapplicable). `manage_jumping`/`manage_jumpclimb` left as cache-only (an early break there could change collision resolution).

**Not done (deferred — would change behavior/structure):**
- **Coarse Y-band filtering** — cheap reject before full AABB:
  ```c
  for(i = 0U; i != levels[currentLvl]->boxes_length; i++)
  {
      box2 = &(levels[currentLvl]->boxes[i]);
      if(box2->y < player.box.y - 32 || box2->y > player.box.y + 32)
          continue;
      if(checkCollision()) { ... }
  }
  ```
- **Pre-sorted collision boxes** by Y at level-load time, then bound the iteration range.
- **Tile-based collision lookup** for static geometry instead of box arrays.

### 4. Inline small functions

```c
// Macro for ultra-hot paths instead of a call:
#define CHECK_COLLISION_FAST() \
    (!(box2->x >= box1->x+box1->w || \
       box2->x+box2->w <= box1->x || \
       box2->y <= box1->y-box1->h || \
       box2->y-box2->h >= box1->y))
```
Or use GBDK-2020's `inline` keyword: `inline UBYTE checkCollision(void) NONBANKED { ... }`

### 5. Use unsigned comparisons

Signed comparisons generate more code:
```c
// Slower (signed)
BYTE vely; if(vely > 3) ...
// Faster (unsigned, where logic permits)
UBYTE vely; if(vely > 3U) ...
```

### 6. Animation timer optimization

Current pattern uses multiple discrete `if` checks:
```c
if(player.timer == 5U)  player.img_index++;
if(player.timer == 10U) player.img_index++;
if(player.timer == 15U) player.img_index++;
if(player.timer == 20U) { player.timer = 0U; player.img_index = 0U; }
```
Consider a modulo-free counter (power-of-2 frame count):
```c
player.timer++;
player.timer &= 0x1F;          // wrap at 32 instead of 20
player.img_index = player.timer >> 3;  // divide by 8 for 4 frames
```

### 7. Level tilemap loading — ✅ IMPLEMENTED (2026-07-08)

`game_screen.c` used to call `set_bkg_tiles()` 360 times per load (once per tile), in **two** identical nested loops (`switch_to_level` and `init_screen`). Both are now a single batched call — the tilemap is a contiguous row-major 20×18 array, and the loads run with the LCD off, so this is byte-identical:
```c
set_bkg_tiles(0, 0, 20, 18, levels[currentLvl]->LvlTileMap);
```
Removed 720 calls/level-load and the redundant index math; **bank 0 code shrank ~147 bytes**.

### 8. Sprite batching

- Use `move_metasprite()` for multi-tile sprites
- Batch sprite updates where possible
- Use sprite-hiding techniques that don't iterate all 40 sprites

---

## GBDK-2020 Compiler Optimizations

### Understanding the SDCC backend

1. Register allocation is limited — the Z80/SM83 has few registers
2. Global variables are often faster than locals (no stack frame setup)
3. Function calls are expensive — ~40+ cycles for call/return overhead
4. Struct access can be slow — pointer arithmetic per member access

### Recommended coding patterns

```c
// SLOW: repeated struct access
void update(void) {
    player.x += player.vx;
    player.y += player.vy;
    if(player.x > 160) player.x = 160;
    if(player.y > 144) player.y = 144;
}

// FASTER: cache in locals
void update(void) {
    UBYTE px = player.x + player.vx;
    UBYTE py = player.y + player.vy;
    if(px > 160) px = 160;
    if(py > 144) py = 144;
    player.x = px;
    player.y = py;
}
```

### Const correctness

Use `const` for data that doesn't change — allows placement in ROM:
```c
const UBYTE lookup_table[] = { 0, 1, 2, 3, 4, 5 };
const struct Level level1 = { ... };
```

### Bank annotations

```c
#pragma bank 5
const unsigned char sprite_data[] = { ... };
```

---

## CPU & Memory Considerations

### SM83 CPU timing reference

| Operation | Cycles (approx) |
|-----------|-----------------|
| 8-bit add/sub | 4 |
| 8-bit compare | 4 |
| 16-bit add | 8 |
| 16-bit compare | 8-12 |
| Multiply (software) | 100-200 |
| Divide (software) | 200-400 |
| Function call | 24 (call) + 16 (return) |
| Array index `arr[i]` | 8-20 (depends on type) |
| Struct member `s.x` | 8-16 |
| Struct pointer `s->x` | 12-24 |

### Cycles per frame

- CPU frequency: 4.194304 MHz (DMG), 8.388608 MHz (CGB double speed)
- Cycles per frame: ~70,224 cycles at 59.7 Hz
- VBlank cycles: ~4,560 cycles (only safe time for VRAM writes)

**Budget per frame:**
- Physics/logic: ~20,000-30,000 cycles
- Sprite updates: ~10,000-20,000 cycles
- Sound: ~5,000-10,000 cycles
- Buffer for interrupts/overhead: ~10,000 cycles

### Memory map awareness

| Region | Address | Size | Use |
|--------|---------|------|-----|
| WRAM | 0xC000-0xDFFF | 8KB | Variables, stack |
| HRAM | 0xFF80-0xFFFE | 127 bytes | Fast access, interrupt handlers |
| VRAM | 0x8000-0x9FFF | 8KB | Tiles, maps (VBlank only!) |
| OAM | 0xFE00-0xFE9F | 160 bytes | Sprite attributes (VBlank only!) |

**HRAM optimization** — place frequently accessed variables in HRAM:
```c
__at(0xFF80) UBYTE fast_counter;
```

---

## Sprite & Graphics Performance

### OAM DMA transfer

Instead of individual `move_sprite()` calls, use OAM DMA for bulk updates:
```c
UBYTE shadow_oam[160];  // Shadow OAM in WRAM

void oam_dma_copy(void) NONBANKED {
    DMA_REG = 0xC0;  // Source: 0xC000 (shadow_oam)
    for(UBYTE i = 40; i != 0; i--);  // wait 160 cycles
}
```

### Sprite count management

Game Boy supports 40 sprites, 10 per scanline. Current code (`game_screen.c:728-737`):
```c
if(previous_sprite_index != sprite_index)
{
    for (i=sprite_index; i!=40U; i++)
        move_sprite(i, 0U, 200U);  // Hide unused
}
```
**Optimization:** track max sprites used and only hide changed sprites.

### Metasprite usage

```c
#include <gb/metasprites.h>

const metasprite_t player_metasprite[] = {
    {.dy = 0, .dx = 0, .dtile = 0, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 1, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 2, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 3, .props = 0},
    METASPR_END
};

// Single call replaces multiple set_sprite_tile/move_sprite pairs
move_metasprite(player_metasprite, base_tile, base_sprite, x, y);
```

---

## Collision Detection

### Current implementation

`checkCollision()` is called potentially 100+ times per frame across `manage_static_physics2()`, `manage_static_physics()`, `manage_climbwalk2()`, `manage_climbwalk()`, `manage_jumpclimb()`, `manage_jumping()`.

### Optimization strategies

1. **Broad phase culling** — quick rejection before AABB:
   ```c
   #define BROAD_PHASE_REJECT(b1, b2, threshold) \
       (ABS((b1)->x - (b2)->x) > threshold || ABS((b1)->y - (b2)->y) > threshold)
   ```
2. **Collision layers** — separate boxes by type and only check relevant ones:
   ```c
   typedef struct {
       Box* ground_boxes;   UBYTE ground_count;
       Box* wall_boxes;     UBYTE wall_count;
       Box* hazard_boxes;   UBYTE hazard_count;
   } CollisionLayers;
   ```
3. **Tile-based collision** for static level geometry:
   ```c
   const UBYTE collision_map[45];  // 1 bit per 8x8 tile, 20x18 grid
   UBYTE is_solid_tile(UBYTE x, UBYTE y) {
       UBYTE tile_x = x >> 3, tile_y = y >> 3;
       UBYTE byte_index = (tile_y * 3) + (tile_x >> 3);
       UBYTE bit_index = tile_x & 7;
       return (collision_map[byte_index] >> bit_index) & 1;
   }
   ```

---

## Sound Performance

### Current implementation (`sound.c`)

Direct hardware register writes are already efficient:
```c
NR10_REG = gSounds[sound].data.chan1.nr10;
NR11_REG = gSounds[sound].data.chan1.nr11;
// ...
```

> [!note] Related open item
> `sound.c:101`'s `if(!ENABLE_SOUND) return;` triggers an unreachable-code warning today because `ENABLE_SOUND` is compiled to `1`. See [[WARNINGS_FIX_PLAN#Remaining Work|Task B in the Warnings Fix Plan]] for the fix.

### GBT Player considerations

`gbt_update()` is called every frame. Consider:
- Calling it every other frame if CPU is tight (30 Hz update still sounds fine)
- Driving it from the VBlank interrupt instead of the main loop:
  ```c
  void vblank_isr(void) {
      gbt_update();
  }
  ```

### Sound priority

Not implemented — would prevent important sounds from being cut off:
```c
typedef enum { PRIORITY_LOW = 0, PRIORITY_NORMAL = 1, PRIORITY_HIGH = 2 } SoundPriority;

UBYTE current_priority[4] = {0, 0, 0, 0};  // Per channel

void play_sound_priority(SoundID sound, SoundPriority priority) {
    UBYTE channel = gSounds[sound].channel;
    if(priority >= current_priority[channel]) {
        play_sound(sound);
        current_priority[channel] = priority;
    }
}
```

---

## Banking Best Practices

### Current bank layout (4 banks, 64 KB) — post-consolidation

| Bank | Size Used | Contents |
|------|-----------|----------|
| 0 | 8,634 bytes | Fixed (`NONBANKED` functions, main, box_collision, sound, gbt_player) |
| 1 | 4,877 bytes | All sprite/UI data |
| 2 | 12,753 bytes | physics, levels, tilemaps, game_screen |
| 3 | 10,103 bytes | Screens (titlescreen2, kwakwa, staffroll), music, gbt bank1 |

See [[#Banking Consolidation Strategy]] above for how the old 8-bank layout was merged and the per-file Makefile/`.area` changes.

### Bank switching cost {#bank-switching-cost}

`SWITCH_ROM_MBC5()` takes ~20-30 cycles. Before consolidation the main loop switched bank 6 (physics) then bank 7 (doggy/player sprites) every frame. After consolidation physics, doggy sprites, and player sprites all live in **bank 2**, so those per-frame switches now target the same bank (the old 6↔7 churn is gone):
```c
SWITCH_ROM_MBC5(2);  // physics, doggy + player sprites (all bank 2 now)
SWITCH_ROM_MBC5(1);  // only when (re)loading sprite tile data
```

### Optimization tips

1. Colocate frequently-used data — put data accessed together in the same bank
2. Minimize switches in hot loops — current code switches outside loops, which is already correct
3. Use `NONBANKED` for small, hot functions — already done for `checkCollision()`
4. Consider bank 0 space — most critical code should live in bank 0 if it fits
5. Consolidate sparse banks — banks 2, 4, 7, 8 are each under 3 KB; merge them

### Far pointers

For data accessed across banks:
```c
#include <gb/far_ptr.h>

FAR_PTR far_data = TO_FAR_PTR(data_in_bank_5, 5);
UBYTE value = FAR_PEEK(far_data);
```

---

## Profiling & Debugging

### BGB emulator profiler

1. Open BGB and load `SRJailbreak.gb` with the `.sym` file
2. Right-click → Other → Profile
3. Run the game, then analyze hotspots

### DIV register timing

```c
UBYTE start = DIV_REG;
// ... code to measure ...
UBYTE elapsed = DIV_REG - start;  // each DIV tick = 256 CPU cycles
```

### Frame timing indicator

```c
void game_screen(void) NONBANKED
{
    while(!finish)
    {
        BGP_REG = 0xE4;      // frame start
        // ... game logic ...
        BGP_REG = 0x1B;      // work done, inverted palette (before vsync)
        vsync();
        BGP_REG = 0xE4;      // restore normal palette
    }
}
```
If the screen flashes inverted colors, you're taking too long.

### Symbol file usage

The build generates `SRJailbreak.sym`. Load it in BGB/Emulicious for function names in the debugger, breakpoints by symbol name, and labeled memory inspection.

### Common performance bugs

1. Forgetting the `U` suffix — `5` vs `5U` may generate signed code
2. Unnecessary bank switches — check if data is already in the current bank
3. VRAM writes outside VBlank — visual corruption *and* wasted cycles waiting
4. Stack overflow — deep recursion or large local arrays
5. Uninitialized variables — unpredictable behavior and extra generated code

---

## Quick Reference Checklist

| Before | Now (✅ achieved 2026-07-08) |
|--------|------------------------------|
| MBC1+RAM+BAT (0x03) | MBC5 (0x19) |
| 256 KB ROM | 64 KB ROM |
| 8 KB RAM | No RAM |
| 8 banks used | 4 banks used |

See [[#Target Configuration — MBC5, 64 KB|Target Configuration]] for the Makefile flags.

### CPU performance
- [ ] Using `UBYTE`/`BYTE` instead of `int`/`short`
- [ ] No division/modulo (use bit shifts for powers of 2)
- [x] Hot functions marked `NONBANKED`
- [x] Compiler optimizations enabled (`-Wf--opt-code-size`; `--max-allocs-per-node` still open)
- [x] Collision detection has early-exit conditions *(plus UBYTE loop bound + safe breaks, 2026-07-08)*
- [ ] Sprite count tracked, unused sprites hidden efficiently
- [x] Bank switches minimized in main loop *(6↔7 churn collapsed into bank 2)*
- [x] Using `const` for ROM data
- [ ] No VRAM writes outside VBlank
- [x] Global variables for frequently-accessed data

### ROM size optimization (target: 64 KB)
See [[#ROM Size Reduction Checklist]] above — duplicated here previously, consolidated to one list.

### RAM optimization
- [ ] Reuse buffers for mutually exclusive data (union)
- [ ] Pack boolean flags into single bytes (bitfields)
- [ ] No `int` where `UBYTE` suffices
- [ ] Avoid large local arrays (use globals)
- [ ] Level entity data shares memory where possible

---

## Resources

- [GBDK-2020 Documentation](https://gbdk-2020.github.io/gbdk-2020/docs/api/)
- [Pan Docs (Game Boy Technical Reference)](https://gbdev.io/pandocs/)
- [GB ASM Tutorial](https://eldred.fr/gb-asm-tutorial/)
- [SDCC Manual](http://sdcc.sourceforge.net/doc/sdccman.pdf)
- [Awesome Game Boy Development](https://github.com/gbdev/awesome-gbdev)

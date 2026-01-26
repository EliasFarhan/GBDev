# CLAUDE.md - SRJailbreak Game Boy Project

## Project Overview

**SRJailbreak** is a Game Boy homebrew platformer where the player controls "Peanut" through 15 levels across 3 worlds. Features include climbing, jumping, physics simulation, key collection, door unlocking, and enemy encounters (seagulls and guards).

## Build System

### Compiler
- **GBDK-2020** (GameBoy Developers Kit) located at `/opt/gbdk-2020/`
- Compiler: `/opt/gbdk-2020/bin/lcc`

### Build Commands
```bash
make          # Build the ROM (outputs SRJailbreak.gb)
make clean    # Remove all build artifacts
```

### Build Output
- `SRJailbreak.gb` - The compiled ROM (256KB, MBC1+RAM+BATT)
- `SRJailbreak.map` - Linker map file
- `SRJailbreak.sym` - Symbol file for debugging

## Project Structure

```
GBDev/
├── src/              # Core game source code (C)
├── data/             # Game assets (sprites, tiles, music)
│   └── map/          # Level tilemap data (15 levels)
├── levels/           # Level definitions and physics handlers
├── tools/            # Dev tools (mod2gbt, json2c.py, etc.)
├── doc/              # Reference documentation (GBDK, CPU manual)
├── examples/         # Example GB projects
├── utils/            # Utility code (reset_graphics.c)
└── Makefile          # Build configuration
```

## Key Source Files

### Core Game (`src/`)
| File | Purpose |
|------|---------|
| `main.c` | Entry point, main game loop (kwakwa → title → game → credits) |
| `game_screen.c` | Core gameplay, rendering, input handling, sprite management |
| `game_screen.h` | Main header with enums, structs, sprite definitions |
| `physics.c` | Collision detection, physics simulation, level-specific logic |
| `box_collision.c` | AABB collision detection (`checkCollision()`) |
| `sound.c` | Sound effects using GB audio hardware |
| `title_screen.c` | Title screen with animated "PRESS START" |
| `credits.c` | Staff roll screen |
| `kwakwa_screen.c` | Logo/intro screen |
| `gbt_player.s` | GBT Player music engine (assembly) |

### Key Data Structures (`game_screen.h`)

```c
// Game states
enum AnimationState { IDLE, WALK, JUMP, CROUCH, CROUCHWALK,
                      CROUCHTRANSITIONIN, CROUCHTRANSITIONOUT,
                      CLIMB, CLIMBWALK, JUMPCLIMB, DEAD };

// Main structs
struct PLAYER    // Player character with position, state, velocity
struct SEAGULL   // Flying enemy with collision, direction, health
struct DOGGY     // Guard enemy with patrol bounds
struct KEY       // Collectible key
struct LOCK      // Door lock tied to collision boxes
struct Level     // Container for all level data
```

## Assets

### Sprites (`data/`)
- `peanut.s` - Player character (108 animation frames)
- `guard.s` - Guard enemy (48 frames)
- `seagull.s` - Flying enemy (16 frames)
- `white_fur.s` - Bonus character
- `environment.s` - Environmental objects (9 frames)
- `background.s` - Background tiles

### Audio
- `music_output.c` - Game music (GBT format)
- `title_screen_music.c` - Title screen music
- Sound effects defined in `sound.c` (JUMP, UNLOCK, KILL, DEAD)

### Levels (`data/map/`)
- 15 level maps: `level1_map.c` through `level15_map.c`
- Each contains: tilemap, collision boxes, locks, level structure

## Tools

### Python Scripts (`tools/`)
- `json2c.py` - Converts Tiled JSON exports to C level data
- `merge_gbs.py` - Optimizes sprite sheets by merging repeated tiles
- `bin2png.py` - Binary to PNG conversion

### External Tools
- **Tiled** (v1.4.3) - Level editor (exports to JSON)
- **GBTD/GBTK** - Tile/sprite editors (Windows, run via Wine)
- **mod2gbt** - Converts MOD music to GBT format

## Memory Banking

The project uses MBC1 ROM banking:
- Banks are allocated via `-Wf-bo#` flags in Makefile
- RAM banking enabled with `ENABLE_RAM_MBC1` / `SWITCH_ROM_MBC1` macros

## Sound System

Direct Game Boy audio register manipulation:
- Channel 1 (NR10-NR14): Square wave with sweep
- Channel 2 (NR21-NR24): Square wave
- Channel 4 (NR41-NR44): Noise channel
- GBT Player for background music

## Development Notes

- Level physics handlers follow pattern: `manage_physics_lvl#()` and `reset_lvl#()`
- Sprite frames indexed via `PeanutTileMap[]`, `GuardTileMap[]`, etc.
- Collision uses AABB box detection
- World progression: World 1 ends at Level 6, World 2 ends at Level 11

## Useful Commands

```bash
# Build ROM
make

# Clean build artifacts
make clean

# Convert Tiled level to C (example)
python tools/json2c.py data/map/level1.json > data/map/level1_map.c
```

## Documentation References

- `/doc/GBCPUman.pdf` - Game Boy CPU manual
- `/doc/gbdk-doc.pdf` - GBDK documentation

# PERFORMANCE.md - Game Boy Performance Guide for SRJailbreak

This document covers performance considerations, optimizations, and best practices for this GBDK-2020 Game Boy project.

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

**MBC1 ROM Sizes:**
| Banks | Size | Hex Header Value |
|-------|------|------------------|
| 2 | 32 KB | 0x00 |
| 4 | 64 KB | 0x01 |
| 8 | 128 KB | 0x02 |
| 16 | 256 KB | 0x03 |
| 32 | 512 KB | 0x04 |
| 64 | 1 MB | 0x05 |
| 128 | 2 MB | 0x06 |

**MBC1 RAM Sizes:**
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

#### MBC5 (Most common for later games)

| Type Code | ROM Size | RAM Size | Notes |
|-----------|----------|----------|-------|
| 0x19 | Up to 8 MB | None | ROM only |
| 0x1A | Up to 8 MB | Up to 128 KB | With RAM |
| 0x1B | Up to 8 MB | Up to 128 KB | With RAM + Battery |
| 0x1C | Up to 8 MB | None | With Rumble |
| 0x1D | Up to 8 MB | Up to 128 KB | Rumble + RAM |
| 0x1E | Up to 8 MB | Up to 128 KB | Rumble + RAM + Battery |

**MBC5 ROM Sizes:**
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

**MBC5 RAM Sizes:**
| Banks | Size | Hex Header Value |
|-------|------|------------------|
| 0 | None | 0x00 |
| 1 | 8 KB | 0x02 |
| 4 | 32 KB | 0x03 |
| 16 | 128 KB | 0x04 |
| 8 | 64 KB | 0x05 |

#### Other MBCs (Less Common)

| Type Code | Name | ROM Size | RAM Size | Notes |
|-----------|------|----------|----------|-------|
| 0x0B-0x0D | MMM01 | Varies | Varies | Multi-cart mapper |
| 0x20 | MBC6 | Up to 2 MB | Up to 32 KB | Flash memory support |
| 0x22 | MBC7 | Up to 2 MB | 256 bytes | Accelerometer + EEPROM |
| 0xFC | Pocket Camera | 1 MB | 128 KB | GB Camera |
| 0xFD | Bandai TAMA5 | 512 KB | 32 bytes | Tamagotchi games |
| 0xFE | HuC3 | Up to 2 MB | 128 KB | Hudson mapper |
| 0xFF | HuC1 | Up to 2 MB | 32 KB | Hudson mapper + IR |

### MBC5 Size Options

| ROM Size | Banks | Header Value | Feasibility for SRJailbreak |
|----------|-------|--------------|----------------------------|
| **64 KB** | 4 | 0x01 | ★ **TARGET** - fits ~37 KB data |
| 128 KB | 8 | 0x02 | Fallback - comfortable fit |
| 256 KB | 16 | 0x03 | Current (wasteful) |
| 512 KB | 32 | 0x04 | Overkill |
| 1 MB+ | 64+ | 0x05+ | Not needed |

**All configurations use MBC5 (0x19) for cartridge type.**

### Current Project Configuration

```
ROM Type: MBC1+RAM+BATTERY (0x03)
ROM Size: 256 KB (16 banks, header 0x03)
RAM Size: 8 KB (1 bank, header 0x02)
```

### Target Configuration (MBC5)

```
ROM Type: MBC5 (0x19)
ROM Size: 64 KB (4 banks, header 0x01)
RAM Size: None (0x00)
```

**Why MBC5:**
- Best compatibility with modern flash chips
- No bank switching bugs (unlike MBC1)
- Industry standard for physical cartridge production
- Widely available reproduction PCBs

---

### Best ROM Types for Physical Cartridges

When manufacturing real Game Boy cartridges, consider these factors:

#### Target: MBC5 (64 KB - 8 MB) ★ RECOMMENDED

| Pros | Cons |
|------|------|
| Most compatible with modern flash chips | Slightly more complex PCB |
| Widely supported by reproduction PCBs | MBC5 chip needed |
| No bank switching bugs (unlike MBC1) | |
| Supports large ROM and RAM | |
| Industry standard for late GB/GBC games | |

**Best for:** Most homebrew projects

**Common configurations:**
| Config | ROM | RAM | Use Case |
|--------|-----|-----|----------|
| MBC5 (0x19) | 64 KB - 2 MB | None | Games without saves |
| MBC5+RAM+BAT (0x1B) | 64 KB - 2 MB | 8-32 KB | Games with saves |

**PCB/Cartridge sources:**
- **InsideGadgets** - New PCBs, various sizes
- **Catskull Electronics** - Quality reproduction boards
- **HDR** (Hand Held Legend) - Flash carts
- **Ferrante Crafts** - Custom PCBs
- **AliExpress** - Budget reproduction boards (variable quality)

---

#### Alternative: No MBC (32 KB)

| Pros | Cons |
|------|------|
| Simplest PCB design | Limited to 32 KB |
| Cheapest to produce | Would require cutting ~5 KB from game |
| No MBC chip needed | No save capability |

**Not recommended for SRJailbreak** - would require removing features.

---

#### Alternative: MBC1 (32 KB - 2 MB)

| Pros | Cons |
|------|------|
| Very common, easy to salvage | Bank switching quirk (>1MB needs care) |
| Well documented | Less compatible with some flash chips |
| Cheaper donor cartridges | Older design than MBC5 |

**Not recommended** - MBC5 is superior for new production.

---

#### Avoid for Physical Carts

| MBC Type | Reason |
|----------|--------|
| MBC2 | Weird 4-bit RAM, limited ROM size |
| MBC3 | RTC adds complexity, battery drain |
| MBC6/MBC7 | Rare, hard to source, special features |
| HuC1/HuC3 | Proprietary Hudson chips, unavailable |

**Stick with MBC5 for best results.**

---

### Physical Cartridge Target: MBC5

#### Primary: MBC5 + 64 KB ★ TARGET
```
ROM Type: MBC5 (0x19)
ROM Size: 64 KB (4 banks)
RAM Size: None
Cost: ~$8-15 per unit
Components: MBC5 chip + 64KB Flash (29F040 or similar)
```

**This is the target configuration for SRJailbreak.**

Current data (~37 KB) fits with room to spare.

#### Fallback: MBC5 + 128 KB
```
ROM Type: MBC5 (0x19)
ROM Size: 128 KB (8 banks)
RAM Size: None
Cost: ~$10-18 per unit
Components: MBC5 chip + 128KB Flash
```

Use if 64 KB proves too tight after optimization attempts.

---

### Flash Chip Compatibility

| Flash Chip | Size | MBC Compatibility | Notes |
|------------|------|-------------------|-------|
| 29F032 | 4 MB | MBC5 | Common, cheap |
| 29F016 | 2 MB | MBC1, MBC5 | Good availability |
| 29F008 | 1 MB | MBC1, MBC5 | |
| 29F040 | 512 KB | MBC1, MBC5 | |
| 29F020 | 256 KB | MBC1, MBC5 | Good for small games |
| 29F010 | 128 KB | MBC1, MBC5 | |
| 27C512 | 64 KB | No MBC, MBC1, MBC5 | EPROM (needs UV eraser) |
| 27C256 | 32 KB | No MBC | EPROM, simplest option |

---

### GBDK-2020 Header Configuration

Set ROM/MBC type in Makefile:
```makefile
# For MBC5, 64KB ROM, no RAM:
LCCFLAGS += -Wl-yt0x19 -Wl-yo4 -Wl-ya0

# For MBC5, 128KB ROM, 8KB RAM with battery:
LCCFLAGS += -Wl-yt0x1B -Wl-yo8 -Wl-ya2

# For No MBC, 32KB ROM:
LCCFLAGS += -Wl-yt0x00 -Wl-yo2 -Wl-ya0
```

| Flag | Meaning |
|------|---------|
| `-Wl-yt0xNN` | Cartridge type (MBC) |
| `-Wl-yoN` | ROM size (N = number of banks) |
| `-Wl-yaN` | RAM size (0=none, 2=8KB, 3=32KB) |

---

### Cost Comparison (MBC5 Options)

| Configuration | PCB Cost | Components | Total (per unit) |
|---------------|----------|------------|------------------|
| **MBC5, 64 KB** ★ | $5-10 | $3-6 | **$8-15** |
| MBC5, 128 KB | $5-10 | $4-8 | **$9-18** |
| MBC5, 256 KB | $5-10 | $5-10 | **$10-20** |

Prices vary by quantity and source. Shell/case adds $2-5.

**Target: MBC5 + 64 KB = ~$8-15 per cartridge**

---

### Target for SRJailbreak: MBC5 + 64 KB

| Specification | Value |
|---------------|-------|
| **Cartridge Type** | MBC5 (0x19) |
| **ROM Size** | 64 KB (4 banks) |
| **RAM Size** | None |
| **Save Feature** | Not required |

**Why this configuration:**
- Current data (~37 KB) fits with ~27 KB headroom
- Best flash chip compatibility (29F040, 29F020, etc.)
- Widely available PCBs (InsideGadgets, Catskull, etc.)
- No battery needed (no save RAM)
- Estimated cost: $8-15 per cartridge

**Makefile configuration for MBC5 64KB:**
```makefile
# MBC5, 64KB ROM (4 banks), no RAM
LCCFLAGS += -Wl-yt0x19 -Wl-yo4 -Wl-ya0
```

**Fallback: MBC5 + 128 KB**

If 64 KB proves too tight after optimization:
```makefile
# MBC5, 128KB ROM (8 banks), no RAM
LCCFLAGS += -Wl-yt0x19 -Wl-yo8 -Wl-ya0
```

---

### Current ROM Configuration

| Metric | Value |
|--------|-------|
| **Total ROM Size** | 262,144 bytes (256 KB) |
| **Actual Data Used** | ~36,749 bytes (14.0%) |
| **Unused/Padding** | ~225,395 bytes (86.0%) |
| **ROM Type** | MBC1+RAM+BATTERY |
| **Banks Used** | 8 of 16 (banks 0, 2, 3, 4, 5, 6, 7, 8) |

### Bank Usage Breakdown

| Bank | Section | Size (bytes) | Contents |
|------|---------|--------------|----------|
| 0 | _CODE | 1,576 | Main loop, sound, GBT stubs |
| 0 | _HOME | 6,520 | NONBANKED functions (game_screen, collision, etc.) |
| 0 | _INITIALIZER | 713 | Initialized data |
| 0 | Headers | ~350 | System headers |
| **0 Total** | | **9,159** | |
| 2 | _CODE_2 | 1,516 | Music data (song0-3, victory) |
| 3 | _CODE_3 | 4,264 | kwakwa_logo, titlescreen2 graphics |
| 4 | _CODE_4 | 1,649 | GBT player bank 1 |
| 5 | _CODE_5 | 4,877 | Sprites (peanut, guard, seagull, etc.) |
| 6 | _CODE_6 | 10,167 | Physics code, level tilemaps |
| 7 | _CODE_7 | 2,443 | Doggy sprites, player sprite management |
| 8 | _CODE_8 | 2,674 | Credits, staffroll graphics |

### Detailed Asset Sizes

#### Graphics Assets (~12,765 bytes)

| Asset | Size | Notes |
|-------|------|-------|
| **tile_peanut** | 1,730 bytes | 108 animation frames (player) |
| **tilemap_peanut** | 122 bytes | Frame index mapping |
| **tile_guard** | 770 bytes | 48 frames (enemy) |
| **tile_seagull** | 258 bytes | 16 frames (flying enemy) |
| **tilemap_seagull** | 20 bytes | Frame mapping |
| **tile_environment** | 306 bytes | 9 frames |
| **tile_background** | 130 bytes | Background tiles |
| **tile_whale_poster** | 770 bytes | In-game decoration |
| **tile_white_fur** | 18 bytes | Bonus character |
| **tile_white_background** | 514 bytes | |
| **press_start** | 237 bytes | UI element |
| **titlescreen2** | 3,420 bytes | Title screen (merged) |
| **kwakwa_logo** | 2,124 bytes | Intro logo (merged) |
| **staffroll** | 2,346 bytes | Credits screen (merged) |

#### Level Data (~6,240 bytes)

| Asset | Size | Notes |
|-------|------|-------|
| **15 Level Tilemaps** | 5,400 bytes | 360 bytes each (20x18 tiles) |
| **Collision boxes** | ~300 bytes | ~5 boxes per level average |
| **Entity metadata** | ~540 bytes | Keys, locks, enemies, doggies |

#### Music & Sound (~3,745 bytes)

| Asset | Size | Notes |
|-------|------|-------|
| **GBT Player (bank 0)** | 254 bytes | Music driver stub |
| **GBT Player (bank 4)** | 1,649 bytes | Full music engine |
| **song0** | 298 bytes | Gameplay music |
| **song1** | 313 bytes | |
| **song2** | 314 bytes | |
| **song3** | 323 bytes | |
| **victory_song** | 268 bytes | |
| **title_song** | 326 bytes | Title screen music |

#### Game Code (~15,557 bytes)

| Module | Size | Location |
|--------|------|----------|
| **game_screen.c** | ~4,500 bytes | Bank 0 (NONBANKED) |
| **physics.c** | ~3,600 bytes | Bank 6 |
| **manage_doggy_sprites** | ~1,750 bytes | Bank 7 |
| **GBDK runtime** | ~1,800 bytes | Bank 0 |
| **Level handlers (1-6)** | ~1,200 bytes | Bank 6 |
| **Level handlers (7-13)** | ~800 bytes | Bank 6 |
| **sound.c** | ~440 bytes | Bank 0 |
| **title_screen.c** | ~400 bytes | Bank 0 |
| **credits.c** | ~200 bytes | Bank 0 |
| **kwakwa_screen.c** | ~100 bytes | Bank 0 |

### RAM Usage

| Section | Address | Size | Contents |
|---------|---------|------|----------|
| Shadow OAM | 0xC000 | 160 bytes | Sprite attribute buffer |
| _DATA | 0xC0A0 | 172 bytes | Runtime variables |
| _INITIALIZED | 0xC14C | 713 bytes | Level data, player, enemies |
| _HRAM | 0xFF80 | 19 bytes | Fast-access variables |
| Stack | ~0xDFxx | ~256 bytes | Call stack |
| **TOTAL** | | **1,320 bytes** | **16.1% of 8KB WRAM** |

---

## ROM Size Optimization Goal

### Target: MBC5 with Smallest ROM

Current 256KB ROM is heavily underutilized (14%). The goal is to fit everything into the **smallest MBC5 configuration** possible.

| ROM Size | Banks | MBC5 Type | Feasibility |
|----------|-------|-----------|-------------|
| **64 KB** | 4 | MBC5 (0x19) | **Primary Target** - requires consolidation |
| 128 KB | 8 | MBC5 (0x19) | Easy - current data fits with room |
| 256 KB | 16 | MBC5 (0x19) | Current size (wasteful) |

**Primary Goal: MBC5 + 64 KB ROM (no RAM)**

### Space Budget for 64KB Target

| Bank | Budget | Planned Contents |
|------|--------|------------------|
| 0 (fixed) | 16,384 bytes | Core code, NONBANKED functions, runtime |
| 1 | 16,384 bytes | All sprites, UI graphics |
| 2 | 16,384 bytes | Level tilemaps, physics, level handlers |
| 3 | 16,384 bytes | Full-screen graphics, music, credits |
| **Total** | **65,536 bytes** | |

Current data (~37KB) leaves ~28KB headroom in 64KB ROM.

---

### Graphics Optimization Strategies

#### 1. Reduce Player Animation Frames

Current: 108 frames (1,730 bytes)

Many frames may be redundant or could use horizontal flipping:
```c
// Instead of storing left-facing frames separately,
// use OAM flip flag (bit 5 of sprite attributes)
set_sprite_prop(sprite_id, S_FLIPX);  // Mirror sprite horizontally
```

**Potential savings**: 40-50% of player sprites (~700-850 bytes)

#### 2. Merge Duplicate Tiles in Sprites

The `merge_gbs.py` tool is already used for full-screen graphics. Apply it to sprite sheets:
```bash
python tools/merge_gbs.py data/peanut.s > data/peanut_merge.s
```

#### 3. Remove Unused Full-Screen Graphics

If any screens are redundant (e.g., similar title/credits backgrounds), consolidate them.

#### 4. Use 1bpp Tiles Where Possible

For simple graphics (text, UI), use 1bpp encoding instead of 2bpp:
```c
// 2bpp: 16 bytes per 8x8 tile
// 1bpp: 8 bytes per 8x8 tile (50% savings)
```

#### 5. Tile Deduplication Across Levels

Many levels likely share common tiles (floors, walls). Use a shared tileset:
```c
// Instead of: 15 separate 360-byte tilemaps
// Use: 1 shared tileset + 15 smaller index maps
```

**Potential level savings**: 20-30% (~1,000-1,500 bytes)

---

### Code Size Optimization

#### 1. Use `--opt-code-size` Compiler Flag

```makefile
CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j --opt-code-size
```

#### 2. Eliminate Redundant Level Handler Functions

Current: Separate `manage_physics_lvl1()` through `manage_physics_lvl15()` and `reset_lvl1()` through `reset_lvl15()`.

Consolidate into data-driven approach:
```c
// Instead of 15 separate functions:
void manage_physics_lvl1(void) { /* level 1 specific */ }
void manage_physics_lvl2(void) { /* level 2 specific */ }
// ...

// Use single parameterized function:
void manage_physics_level(UBYTE level_id) {
    // Use level_id to index into data tables
}
```

**Potential savings**: 2,000-4,000 bytes

#### 3. Use Lookup Tables Instead of Switch Statements

```c
// LARGER: Switch statement
switch(state) {
    case IDLE: handle_idle(); break;
    case WALK: handle_walk(); break;
    // ...
}

// SMALLER: Function pointer table
typedef void (*StateHandler)(void);
const StateHandler handlers[] = { handle_idle, handle_walk, ... };
handlers[state]();
```

#### 4. Remove Debug Code

Ensure no `printf`, logging, or debug-only code remains in release builds.

#### 5. Inline Trivial Functions

Very small functions have call/return overhead. Use macros:
```c
// Instead of:
void set_flag(UBYTE flag) { player.booleanState |= flag; }

// Use:
#define SET_FLAG(f) (player.booleanState |= (f))
```

---

### Music & Sound Optimization

#### 1. Consider Smaller Music Driver

GBT Player uses ~1,900 bytes. Alternatives:
- **hUGEDriver**: Smaller footprint
- **Custom minimal driver**: If only simple SFX needed

#### 2. Reduce Song Count

If songs are similar, consider reusing patterns or removing redundant tracks.

#### 3. Compress Music Data

GBT format is already compact, but pattern reuse can reduce size further.

---

### Banking Consolidation Strategy

#### Current: 8 Banks Used

```
Bank 0: Core (9,159 bytes)
Bank 2: Music (1,516 bytes)
Bank 3: Logo/Title (4,264 bytes)
Bank 4: GBT Bank1 (1,649 bytes)
Bank 5: Sprites (4,877 bytes)
Bank 6: Physics/Levels (10,167 bytes)
Bank 7: Doggy/Player (2,443 bytes)
Bank 8: Credits (2,674 bytes)
```

#### Target: 4 Banks

```
Bank 0 (16KB): Core code + runtime + NONBANKED
  - Current _CODE: 1,576
  - Current _HOME: 6,520
  - Current _INITIALIZER: 713
  - Add: sound.c, title logic
  - Remaining: ~7,000 bytes free

Bank 1 (16KB): All Sprites + UI
  - Peanut: 1,852
  - Guard: 770
  - Seagull: 278
  - Environment: 306
  - Background: 130
  - White fur: 18
  - Whale poster: 770
  - Press start: 237
  - Total: ~4,361 bytes
  - Remaining: ~12,000 bytes free

Bank 2 (16KB): Levels + Physics
  - 15 tilemaps: 5,400
  - Physics code: 3,600
  - Level handlers: 2,000 (consolidated)
  - Collision data: 840
  - Total: ~11,840 bytes
  - Remaining: ~4,500 bytes free

Bank 3 (16KB): Screens + Music
  - Titlescreen2: 3,420
  - Kwakwa logo: 2,124
  - Staffroll: 2,346
  - GBT Player: 1,903
  - All songs: 1,842
  - Credits code: 200
  - Total: ~11,835 bytes
  - Remaining: ~4,500 bytes free
```

---

### RAM Optimization

Current RAM usage is healthy (16.1%), but can be reduced:

#### 1. Reuse Buffers

Level-specific data (collision boxes, enemies) can share memory:
```c
// Instead of separate arrays per level type:
union LevelEntities {
    struct { SEAGULL seagulls[4]; } flying_level;
    struct { DOGGY doggies[2]; } guard_level;
};
```

#### 2. Reduce Struct Sizes

Pack related flags into bitfields:
```c
// Current: Multiple UBYTE flags
UBYTE groundContact;
UBYTE frontContact;
UBYTE wallContact;

// Optimized: Single byte with bits
UBYTE contactFlags;  // bit 0: ground, bit 1: front, bit 2: wall
```

#### 3. Use Smaller Data Types

Ensure no `int` (16-bit) where `UBYTE` (8-bit) suffices.

#### 4. Stack Usage

Avoid large local arrays. Use global buffers instead.

---

### ROM Size Reduction Checklist

- [ ] Apply `--opt-code-size` compiler flag
- [ ] Consolidate level handler functions into data-driven approach
- [ ] Use sprite flipping instead of storing mirrored frames
- [ ] Run tile merger on all sprite sheets
- [ ] Remove any unused graphics/code
- [ ] Consolidate banks to 4
- [ ] Replace switch statements with lookup tables
- [ ] Review and remove any debug code
- [ ] Consider smaller music driver
- [ ] Use shared tilesets across levels

### Expected Results

| Optimization | Estimated Savings |
|--------------|-------------------|
| Sprite flipping | 700-850 bytes |
| Level handler consolidation | 2,000-4,000 bytes |
| `--opt-code-size` | 500-1,000 bytes |
| Tile deduplication | 1,000-1,500 bytes |
| Music driver swap | 500-800 bytes |
| **Total potential** | **4,700-8,150 bytes** |

After optimization, ROM should fit comfortably in **64KB** with room to spare.

---

## Current Optimizations

The project already implements several good performance practices:

### Data Types (game_screen.h)
- **8-bit types throughout**: All position, state, and counter variables use `UBYTE`/`BYTE`
- The Z80-derived SM83 CPU is 8-bit; 16-bit operations require multiple instructions
- Structs are compact (e.g., `Box` is 4 bytes, `PLAYER` is ~21 bytes)

### Bitwise State Flags (game_screen.h:7-13)
```c
#define HASJUMP        0x01
#define TRANSITIONNING 0x04
#define HASKEY         0x08
#define HASGAMEOVER    0x10
#define HASVICTORY     0x20
#define WORLD_SWITCH   0x40
```
- Six boolean states packed into a single `UBYTE`
- Uses fast bitwise operations (`&`, `|`, `~`) instead of separate booleans

### NONBANKED Critical Functions
- `checkCollision()`, `game_screen()`, and `switch_to_level()` are marked `NONBANKED`
- These stay in the fixed ROM bank (bank 0) and don't require bank switching

### Early-Exit Collision Detection (box_collision.c:12-19)
```c
UBYTE checkCollision(void) NONBANKED
{
    if(box2->x >= box1->x+box1->w) return 0;
    if(box2->x+box2->w <= box1->x) return 0;
    if(box2->y <= box1->y-box1->h) return 0;
    if(box2->y-box2->h >= box1->y) return 0;
    return 1;
}
```
- Separating axis test with early returns
- Most non-colliding boxes exit after 1-2 comparisons

### Frame-Locked Main Loop (game_screen.c:939-982)
- Uses `vsync()` for consistent 60 FPS timing
- Conditional physics updates (skipped during state transitions)

### Global Loop Counter Reuse
- Single `UBYTE i` reused across all loops
- Avoids stack allocation overhead

---

## Potential Improvements

### 1. Compiler Optimization Flags

**Current Makefile lacks optimization flags.** Add these to the `CC` line:

```makefile
# Recommended optimization flags
CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j --max-allocs-per-node 50000

# Or for aggressive optimization:
CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j --max-allocs-per-node 100000 --opt-code-speed
```

Available GBDK-2020 optimization options:
| Flag | Effect |
|------|--------|
| `--max-allocs-per-node N` | Increase register allocation attempts (default ~3000, try 50000+) |
| `--opt-code-speed` | Optimize for speed over size |
| `--opt-code-size` | Optimize for size (useful if ROM is tight) |
| `--peep-return` | Enable return peephole optimization |
| `--allow-unsafe-read` | Allow potentially unsafe optimizations |

### 2. Replace Division/Modulo with Bitwise Operations

Division and modulo are extremely expensive on the Game Boy (~200+ cycles). Replace where possible:

```c
// SLOW: Division
UBYTE result = value / 8;
UBYTE remainder = value % 8;

// FAST: Bitwise (for powers of 2)
UBYTE result = value >> 3;      // Divide by 8
UBYTE remainder = value & 0x07; // Modulo 8
```

**Check physics.c and game_screen.c for any `/` or `%` operators.**

### 3. Reduce Collision Box Iterations

Currently, physics functions iterate through ALL collision boxes every frame:
```c
for(i = 0U; i != levels[currentLvl]->boxes_length; i++)
```

**Spatial partitioning options:**

a) **Coarse Y-band filtering** - Skip boxes not in player's vertical range:
```c
for(i = 0U; i != levels[currentLvl]->boxes_length; i++)
{
    box2 = &(levels[currentLvl]->boxes[i]);

    // Quick Y-band rejection (cheap check before full AABB)
    if(box2->y < player.box.y - 32 || box2->y > player.box.y + 32)
        continue;

    if(checkCollision()) { ... }
}
```

b) **Pre-sorted collision boxes** - Sort boxes by Y during level load, then binary search or limit iteration range.

c) **Tile-based collision lookup** - For static geometry, use a collision tilemap instead of box arrays.

### 4. Inline Small Functions

GBDK-2020 doesn't always inline small functions. Use macros for tiny operations:

```c
// Instead of:
UBYTE checkCollision(void);

// Consider macro for ultra-hot paths:
#define CHECK_COLLISION_FAST() \
    (!(box2->x >= box1->x+box1->w || \
       box2->x+box2->w <= box1->x || \
       box2->y <= box1->y-box1->h || \
       box2->y-box2->h >= box1->y))
```

Or use the `inline` keyword (GBDK-2020 supports it):
```c
inline UBYTE checkCollision(void) NONBANKED { ... }
```

### 5. Use Unsigned Comparisons

Signed comparisons generate more code. Use unsigned where possible:

```c
// Slower (signed)
BYTE vely;
if(vely > 3) ...

// Faster (unsigned, if logic permits)
UBYTE vely;
if(vely > 3U) ...
```

### 6. Animation Timer Optimization

Current pattern uses multiple `if` statements:
```c
if(player.timer == 5U)  player.img_index++;
if(player.timer == 10U) player.img_index++;
if(player.timer == 15U) player.img_index++;
if(player.timer == 20U) { player.timer = 0U; player.img_index = 0U; }
```

Consider lookup table or bitwise:
```c
// Use modulo-free counter (power of 2 frame count)
player.timer++;
player.timer &= 0x1F;  // Wrap at 32 instead of 20
player.img_index = player.timer >> 3;  // Divide by 8 for 4 frames
```

### 7. Level Tilemap Loading

The level loading loop (game_screen.c:920-933) calls `set_bkg_tiles()` 360 times:
```c
for(i = 0; i != 18; i++)
{
    for(j = 0; j!= 20; j++)
    {
        set_bkg_tiles(j,i,1,1, &(levels[currentLvl]->LvlTileMap)[...]);
    }
}
```

**Optimize with row-based loading:**
```c
// Load entire rows at once (20 tiles per call instead of 1)
for(i = 0; i != 18; i++)
{
    set_bkg_tiles(0, i, 20, 1, &(levels[currentLvl]->LvlTileMap)[i * 20]);
}
```

Or use `set_bkg_tiles(0, 0, 20, 18, tilemap)` for the entire screen at once.

### 8. Sprite Batching

Current sprite rendering makes many individual calls. Consider:
- Using `move_metasprite()` for multi-tile sprites
- Batch sprite updates where possible
- Use sprite hiding techniques that don't iterate all 40 sprites

---

## GBDK-2020 Compiler Optimizations

### Understanding SDCC Backend

GBDK-2020 uses SDCC (Small Device C Compiler). Key behaviors:

1. **Register allocation is limited** - The Z80/SM83 has few registers
2. **Global variables are often faster** than locals (no stack frame setup)
3. **Function calls are expensive** - ~40+ cycles for call/return overhead
4. **Struct access can be slow** - Pointer arithmetic for each member access

### Recommended Coding Patterns

```c
// SLOW: Repeated struct access
void update(void) {
    player.x += player.vx;
    player.y += player.vy;
    if(player.x > 160) player.x = 160;
    if(player.y > 144) player.y = 144;
}

// FASTER: Cache in locals
void update(void) {
    UBYTE px = player.x + player.vx;
    UBYTE py = player.y + player.vy;
    if(px > 160) px = 160;
    if(py > 144) py = 144;
    player.x = px;
    player.y = py;
}
```

### Const Correctness

Use `const` for data that doesn't change - allows placement in ROM:
```c
const UBYTE lookup_table[] = { 0, 1, 2, 3, 4, 5 };
const struct Level level1 = { ... };
```

### Bank Annotations

Ensure data is in the correct bank:
```c
// Place data in specific bank
#pragma bank 5
const unsigned char sprite_data[] = { ... };
```

---

## CPU & Memory Considerations

### SM83 CPU Timing Reference

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

### Cycles Per Frame

- **CPU frequency**: 4.194304 MHz (DMG), 8.388608 MHz (CGB double speed)
- **Cycles per frame**: ~70,224 cycles at 59.7 Hz
- **VBlank cycles**: ~4,560 cycles (only safe time for VRAM writes)

**Budget your frame wisely:**
- Physics/logic: ~20,000-30,000 cycles
- Sprite updates: ~10,000-20,000 cycles
- Sound: ~5,000-10,000 cycles
- Buffer for interrupts/overhead: ~10,000 cycles

### Memory Map Awareness

| Region | Address | Size | Use |
|--------|---------|------|-----|
| WRAM | 0xC000-0xDFFF | 8KB | Variables, stack |
| HRAM | 0xFF80-0xFFFE | 127 bytes | Fast access, interrupt handlers |
| VRAM | 0x8000-0x9FFF | 8KB | Tiles, maps (VBlank only!) |
| OAM | 0xFE00-0xFE9F | 160 bytes | Sprite attributes (VBlank only!) |

**HRAM optimization**: Place frequently accessed variables in HRAM:
```c
__at(0xFF80) UBYTE fast_counter;
```

---

## Sprite & Graphics Performance

### OAM DMA Transfer

Instead of individual `move_sprite()` calls, use OAM DMA for bulk updates:

```c
// Shadow OAM in WRAM
UBYTE shadow_oam[160];

// DMA transfer routine (must be in HRAM)
void oam_dma_copy(void) NONBANKED {
    // Initiate DMA transfer
    DMA_REG = 0xC0;  // Source: 0xC000 (shadow_oam)
    // Wait 160 cycles
    for(UBYTE i = 40; i != 0; i--);
}
```

### Sprite Count Management

Game Boy supports 40 sprites, 10 per scanline. Current code (game_screen.c:728-737):
```c
if(previous_sprite_index != sprite_index)
{
    for (i=sprite_index; i!=40U; i++)
        move_sprite(i, 0U, 200U);  // Hide unused
}
```

**Optimization**: Track max sprites used and only hide changed sprites.

### Metasprite Usage

For multi-tile characters, use GBDK-2020's metasprite functions:
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

### Current Implementation Analysis

The `checkCollision()` function is called potentially 100+ times per frame across:
- `manage_static_physics2()`
- `manage_static_physics()`
- `manage_climbwalk2()`
- `manage_climbwalk()`
- `manage_jumpclimb()`
- `manage_jumping()`

### Optimization Strategies

#### 1. Broad Phase Culling

Add a quick distance check before AABB:
```c
// Quick rejection based on Manhattan distance
#define BROAD_PHASE_REJECT(b1, b2, threshold) \
    (ABS((b1)->x - (b2)->x) > threshold || ABS((b1)->y - (b2)->y) > threshold)
```

#### 2. Collision Layers

Separate collision boxes by type and only check relevant ones:
```c
typedef struct {
    Box* ground_boxes;
    UBYTE ground_count;
    Box* wall_boxes;
    UBYTE wall_count;
    Box* hazard_boxes;
    UBYTE hazard_count;
} CollisionLayers;
```

#### 3. Tile-Based Collision

For static level geometry, use a collision tile map:
```c
// 1 bit per 8x8 tile = 20x18 = 45 bytes per level
const UBYTE collision_map[45];

UBYTE is_solid_tile(UBYTE x, UBYTE y) {
    UBYTE tile_x = x >> 3;  // Divide by 8
    UBYTE tile_y = y >> 3;
    UBYTE byte_index = (tile_y * 3) + (tile_x >> 3);
    UBYTE bit_index = tile_x & 7;
    return (collision_map[byte_index] >> bit_index) & 1;
}
```

---

## Sound Performance

### Current Implementation (sound.c)

Direct hardware register writes are efficient:
```c
NR10_REG = gSounds[sound].data.chan1.nr10;
NR11_REG = gSounds[sound].data.chan1.nr11;
// ...
```

### GBT Player Considerations

`gbt_update()` is called every frame. Consider:
- Call it every other frame if CPU is tight (30 Hz update still sounds good)
- Use the VBlank interrupt to call it instead of main loop

```c
// In VBlank interrupt handler
void vblank_isr(void) {
    gbt_update();
}
```

### Sound Priority

Implement sound priority to prevent important sounds from being cut off:
```c
typedef enum {
    PRIORITY_LOW = 0,
    PRIORITY_NORMAL = 1,
    PRIORITY_HIGH = 2
} SoundPriority;

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

### Current Bank Layout (8 banks, 256KB)

| Bank | Size Used | Contents |
|------|-----------|----------|
| 0 | 9,159 bytes | Fixed (NONBANKED functions, main code) |
| 2 | 1,516 bytes | Music data |
| 3 | 4,264 bytes | Titlescreen, kwakwa logo |
| 4 | 1,649 bytes | GBT player bank 1 |
| 5 | 4,877 bytes | Player sprites, title assets |
| 6 | 10,167 bytes | Physics, levels, seagull, music |
| 7 | 2,443 bytes | Game screen, doggy sprites |
| 8 | 2,674 bytes | Credits, music |

### Target Bank Layout: MBC5 + 64 KB (4 banks)

See [ROM Size Optimization Goal](#rom-size-optimization-goal) for the consolidation plan.

| Bank | Budget | Planned Contents |
|------|--------|------------------|
| 0 | 16 KB | Core code, NONBANKED, sound, title logic |
| 1 | 16 KB | All sprites, UI graphics |
| 2 | 16 KB | Levels, physics, collision |
| 3 | 16 KB | Full-screen graphics, music, credits |

**Makefile target:**
```makefile
# MBC5, 64KB (4 banks), no RAM
LCCFLAGS += -Wl-yt0x19 -Wl-yo4 -Wl-ya0
```

### Bank Switching Cost

`SWITCH_ROM_MBC1()` takes ~20-30 cycles. Currently called twice per frame:
```c
SWITCH_ROM_MBC1(6);  // Before physics
// ...
SWITCH_ROM_MBC1(7);  // Before doggy sprites
```

With 4-bank layout, this reduces to potentially 1 switch per frame.

### Optimization Tips

1. **Colocate frequently-used data** - Put data accessed together in the same bank
2. **Minimize switches in hot loops** - Current code switches outside loops, which is correct
3. **Use NONBANKED for small, hot functions** - Already done for `checkCollision()`
4. **Consider bank 0 space** - Most critical code should be in bank 0 if it fits
5. **Consolidate sparse banks** - Banks 2, 4, 7, 8 are under 3KB each; merge them

### Makefile Bank Assignment

Update Makefile `-Wf-bo#` flags for new layout:
```makefile
# Old (8 banks):
# -Wf-bo3 for titlescreen, -Wf-bo5 for sprites, etc.

# New (4 banks):
# Bank 1: All sprites
data/peanut.o: CFLAGS += -Wf-bo1
data/guard.o: CFLAGS += -Wf-bo1
data/seagull.o: CFLAGS += -Wf-bo1

# Bank 2: Levels and physics
src/physics.o: CFLAGS += -Wf-bo2
data/map/%.o: CFLAGS += -Wf-bo2

# Bank 3: Screens and music
data/titlescreen2.o: CFLAGS += -Wf-bo3
data/kwakwa_logo.o: CFLAGS += -Wf-bo3
src/gbt_player_bank1.o: CFLAGS += -Wf-bo3
```

### Far Pointers

For data accessed across banks:
```c
#include <gb/far_ptr.h>

// Access data in another bank
FAR_PTR far_data = TO_FAR_PTR(data_in_bank_5, 5);
UBYTE value = FAR_PEEK(far_data);
```

---

## Profiling & Debugging

### BGB Emulator Profiler

BGB has a built-in profiler. To use it:
1. Open BGB and load SRJailbreak.gb with the .sym file
2. Right-click > Other > Profile
3. Run the game, then analyze hotspots

### DIV Register Timing

Use the DIV register for quick timing measurements:
```c
UBYTE start = DIV_REG;
// ... code to measure ...
UBYTE elapsed = DIV_REG - start;
// Each DIV tick = 256 CPU cycles
```

### Frame Timing Indicator

Add a visual frame timing indicator:
```c
void game_screen(void) NONBANKED
{
    while(!finish)
    {
        // Set palette to indicate frame start
        BGP_REG = 0xE4;

        // ... game logic ...

        // Set palette to indicate work done (before vsync)
        BGP_REG = 0x1B;  // Inverted palette

        vsync();

        // Restore normal palette
        BGP_REG = 0xE4;
    }
}
```

If the screen flashes inverted colors, you're taking too long.

### Symbol File Usage

The build generates `SRJailbreak.sym`. Load it in BGB/Emulicious for:
- Function names in debugger
- Breakpoints by symbol name
- Memory inspection with labels

### Common Performance Bugs

1. **Forgetting to use `U` suffix** - `5` vs `5U` may generate signed code
2. **Unnecessary bank switches** - Check if data is already in current bank
3. **VRAM writes outside VBlank** - Causes visual corruption AND wastes cycles waiting
4. **Stack overflow** - Deep recursion or large local arrays
5. **Uninitialized variables** - May cause unpredictable behavior and extra code

---

## Quick Reference Checklist

### Target Configuration: MBC5 + 64 KB

```makefile
# Add to Makefile for MBC5, 64KB ROM, no RAM:
LCCFLAGS += -Wl-yt0x19 -Wl-yo4 -Wl-ya0
```

| Current | Target |
|---------|--------|
| MBC1+RAM+BAT (0x03) | MBC5 (0x19) |
| 256 KB ROM | 64 KB ROM |
| 8 KB RAM | No RAM |
| ~37 KB used (14%) | ~37 KB used (57%) |

### CPU Performance
- [ ] Using `UBYTE`/`BYTE` instead of `int`/`short`
- [ ] No division/modulo (use bit shifts for powers of 2)
- [ ] Hot functions marked `NONBANKED`
- [ ] Compiler optimizations enabled (`--max-allocs-per-node`)
- [ ] Collision detection has early-exit conditions
- [ ] Sprite count tracked, unused sprites hidden efficiently
- [ ] Bank switches minimized in main loop
- [ ] Using `const` for ROM data
- [ ] No VRAM writes outside VBlank
- [ ] Global variables for frequently-accessed data

### ROM Size Optimization (Target: 64KB)
- [ ] Apply `--opt-code-size` compiler flag
- [ ] Consolidate level handlers into single data-driven function
- [ ] Use sprite flipping (`S_FLIPX`) instead of storing mirrored frames
- [ ] Run `merge_gbs.py` on all sprite sheets
- [ ] Remove unused graphics and code
- [ ] Consolidate from 8 banks to 4 banks
- [ ] Replace large switch statements with lookup tables
- [ ] Remove all debug/development code
- [ ] Consider smaller music driver (hUGEDriver)
- [ ] Use shared tilesets across levels
- [ ] Ensure no redundant full-screen graphics

### RAM Optimization
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

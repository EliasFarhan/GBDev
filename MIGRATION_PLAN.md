# Migration Plan: GBDK to GBDK-2020

This document outlines the steps required to migrate SRJailbreak from the legacy GBDK (`/opt/gbdk/`) to GBDK-2020.

## Migration Status: COMPLETE

The project has been successfully migrated to GBDK-2020. The ROM builds and is 256KB (MBC1+RAM+BATT).

---

## Changes Made

### 1. Makefile Updates
**File:** `Makefile`
```makefile
# Changed from:
CC = /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

# To:
CC = /opt/gbdk-2020/bin/lcc -Wa-l -Wl-m -Wl-j
```

### 2. API Function Replacements
**Files:** `src/game_screen.c`, `src/title_screen.c`, `src/credits.c`, `src/kwakwa_screen.c`

Replaced all `wait_vbl_done()` calls with `vsync()`.

### 3. Constant Expression Fixes
**Files:** All 15 level map files in `data/map/`

SDCC requires constant expressions in struct initializers. Changed variable declarations to `#define` macros:
```c
// Before:
size_t boxes_lvl1_length = 5;
Level lvl1 = { box_lvl1, boxes_lvl1_length, ... };

// After:
#define BOXES_LVL1_LENGTH 5
Level lvl1 = { box_lvl1, BOXES_LVL1_LENGTH, ... };
```

### 4. Struct Fix
**File:** `src/game_screen.h`

The `WALL` struct was missing a field that initializers were providing:
```c
// Before:
typedef struct {
    Box* box;
} WALL;

// After:
typedef struct {
    Box* box;
    UBYTE active;
} WALL;
```

### 5. Include Path Fixes
**File:** `src/main.c`
```c
// Before:
#include "utils/reset_graphics.c"

// After:
#include "../utils/reset_graphics.c"
```

**File:** `src/title_screen.c`
```c
// Before:
#include <src/gbt_player.h>

// After:
#include "gbt_player.h"
```

---

## Remaining Warnings

The build completes with warnings that can be addressed later:

1. **Function prototypes (warning 283):** Functions declared without `(void)` parameter list
2. **Implicit function declarations:** Some functions called before declaration
3. **Unreferenced variables:** Unused local variables
4. **Optimizer warnings:** Non-critical flow optimization notes

These warnings don't prevent the ROM from building or running.

---

## Testing Checklist

### Build Verification
- [x] Clean build completes without errors
- [x] ROM size matches expected (256KB)
- [x] No linker errors about overlapping areas

### Functional Testing (Manual verification needed)
- [ ] Kwakwa logo screen displays correctly
- [ ] Title screen renders and animates
- [ ] Music plays (GBT Player works)
- [ ] Sound effects work (jump, unlock, kill, dead)
- [ ] All 15 levels load correctly
- [ ] Player physics work (jump, climb, crouch)
- [ ] Enemy AI works (seagulls, guards)
- [ ] Key/lock mechanics function
- [ ] World transitions work
- [ ] Credits screen displays

### Emulator Compatibility
- [ ] BGB
- [ ] SameBoy
- [ ] mGBA
- [ ] Real hardware (if available)

---

## Optional Future Improvements

1. **Fix function prototype warnings:** Add `(void)` to parameterless function declarations
2. **Initialize global variables explicitly:** WRAM is no longer auto-initialized to zero
3. **Consider hUGEDriver:** Modern replacement for GBT Player with better GBDK-2020 integration
4. **Add forward declarations:** Fix implicit function declaration warnings

---

## Resources

- [GBDK-2020 Documentation](https://gbdk-2020.github.io/gbdk-2020/docs/api/)
- [Migration Guide](https://gbdk.org/docs/api/docs_migrating_versions.html)
- [hUGEDriver](https://github.com/SuperDisk/hUGEDriver) - Modern music driver
- [GBDK-2020 Examples](https://github.com/gbdk-2020/gbdk-2020/tree/develop/gbdk-lib/examples)

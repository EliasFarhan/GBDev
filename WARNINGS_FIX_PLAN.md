# Implementation Plan: Fix GBDK-2020 Compiler Warnings

## Warning Summary

| Warning | Count | Description |
|---------|-------|-------------|
| 283 | ~100 | Function declarator with no prototype |
| 112 | 4 | Implicit function declaration |
| 84 | 5 | Variable may be used before initialization |
| 85 | 1 | Unreferenced local variable |
| 94 | 4 | Comparison always true/false due to type range |
| 110 | 2 | Conditional flow changed by optimizer |
| 126 | 3 | Unreachable code |
| 154 | 2 | Converting integral to pointer without cast |
| 158 | 1 | Overflow in implicit constant conversion |

---

## Task 1: Fix Function Prototype Warnings (Warning 283)

**Problem:** SDCC requires `(void)` for functions with no parameters.

### 1.1 Header Files

**File: `src/game_screen.h` (lines 164-169)**
```c
// Before:
void init_screen();
void game_screen();
void game_over();
void switch_to_level(LEVELID);
void switch_to_world(WORLDID);
void reset_game();

// After:
void init_screen(void);
void game_screen(void);
void game_over(void);
void switch_to_level(LEVELID level);
void switch_to_world(WORLDID world);
void reset_game(void);
```

**File: `src/box_collision.h` (line 12)**
```c
// Before:
UBYTE checkCollision();

// After:
UBYTE checkCollision(void);
```

**File: `src/sound.h` (lines 88-89)**
```c
// Before:
void init_sounds();
void tick_sound();

// After:
void init_sounds(void);
void tick_sound(void);
```

### 1.2 Source Files - Function Definitions

All function definitions with `()` need to be changed to `(void)`:

- `src/main.c`: `main()`
- `src/game_screen.c`: Multiple functions
- `src/physics.c`: Multiple level physics functions
- `src/sound.c`: `init_sounds()`, `tick_sound()`
- `src/box_collision.c`: `checkCollision()`
- `src/title_screen.c`: `title_screen()`
- `src/credits.c`: `credits_screen()`
- `src/kwakwa_screen.c`: `kwakwa_screen()`
- `utils/reset_graphics.c`: `disable_APA()`
- `levels/*.c`: All `manage_physics_lvl*()` and `reset_lvl*()` functions

---

## Task 2: Add Forward Declarations (Warnings 112, 84)

**Problem:** Functions called before being declared.

### 2.1 Create/Update Header Files

**File: `src/title_screen.h`** - Ensure it declares:
```c
void title_screen(void);
```

**File: `src/kwakwa_screen.h`** - Ensure it declares:
```c
void kwakwa_screen(void);
```

**File: `src/credits.h`** (create if missing) - Add:
```c
#ifndef CREDITS_H_
#define CREDITS_H_

void credits_screen(void);

#endif
```

### 2.2 Add Includes to main.c

**File: `src/main.c`**
```c
#include "title_screen.h"
#include "kwakwa_screen.h"
#include "credits.h"  // or add forward declaration
```

### 2.3 Fix victory() in level6.c

**File: `levels/level6.c`**

Add forward declaration or include for `victory()` function.

---

## Task 3: Remove Unreferenced Variables (Warning 85)

**File: `src/title_screen.c` (line 107)**
```c
// Before:
UBYTE i, j;

// After:
UBYTE i;
```

---

## Task 4: Fix Type Range Comparisons (Warning 94)

**File: `src/physics.c`**

Lines 37, 457, 479, 488 have comparisons that are always true/false due to UBYTE range (0-255).

Example issues:
- Comparing UBYTE >= 0 (always true)
- Comparing UBYTE < 0 (always false)

Review and fix the logic or change types as needed.

---

## Task 5: Fix Unreachable Code (Warning 126)

**File: `src/sound.c` (line 101)**
- Code after a `return` or `break` statement

**File: `src/physics.c` (lines 480, 489)**
- Dead code branches

Review and remove unreachable statements.

---

## Task 6: Fix Pointer Casts (Warnings 154, 158)

**File: `utils/reset_graphics.c` (lines 50, 51, 54)**

```c
// Before (line 50-51):
add_VBL(NULL);
add_LCD(NULL);

// After:
add_VBL((void (*)(void))0);
add_LCD((void (*)(void))0);

// Or use proper NULL pointer:
add_VBL((int_handler)0);
add_LCD((int_handler)0);
```

---

## Task 7: Fix Uninitialized Variable (Warning 84)

**File: `src/game_screen.c` (line 505)**
```c
// Find 'origin_index' and ensure it's initialized before use
UBYTE origin_index = 0;
```

---

## Implementation Order

| Priority | Task | Files Affected | Estimated Changes |
|----------|------|----------------|-------------------|
| 1 | Fix header prototypes | 3 headers | ~10 lines |
| 2 | Fix source function definitions | ~15 files | ~50 lines |
| 3 | Add forward declarations | main.c, level6.c | ~5 lines |
| 4 | Remove unused variables | title_screen.c | 1 line |
| 5 | Fix pointer casts | reset_graphics.c | 3 lines |
| 6 | Initialize variables | game_screen.c | 1 line |
| 7 | Review type comparisons | physics.c | 4 lines |
| 8 | Remove unreachable code | sound.c, physics.c | 3 lines |

---

## Expected Result

After implementing all fixes:
- **0 warnings** during compilation
- Same ROM output (256KB)
- No functional changes to the game

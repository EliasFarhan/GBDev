#define NUM_COLORS 5
#define NUM_FACES 6

#define YES 1
#define NO  0

#define BOARD_MAX_X 15
#define BOARD_MAX_Y 22

/* Game Types */
#define FAST 0
#define QUEST 1

/* Difficulty levels */
#define EASY 0
#define MEDIUM 1
#define HARD 2
#define EVIL 3

/* Cheat bits */
#define DYNAMITE (1<<0)
#define SLOWDOWN (1<<1)
#define CHEAT_RANDOM_BOARD (1<<2)
#define SHOWLOOP (1<<3)

/* block numbers */
#define cSTAR_COLOR 7

void piecefall (void);
void displaysquare(UBYTE posx, UBYTE posy);
void displaypiece (UBYTE posx, UBYTE posy);
void displaynextpiece (void);
void erasepiece (UBYTE posx, UBYTE posy);
void erasesquare (UBYTE posx, UBYTE posy);

void show_score (void);
void show_combo (void);
void displaynumber (UBYTE y);
void displayspeed (void);
void init_graphics (void);
void play_sound (UBYTE);
void sound_click (void);
void sound_pop (void);
UBYTE wait_for_button (void);

void gameover (void);
void empty_board (void);
void empty_screen (void);


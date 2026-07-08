#include <gb/gb.h>
#include <gb/drawing.h>

#include "game_screen.h"
#include "../utils/reset_graphics.c"
#include "gbt_player.h"

// Forward declarations
void kwakwa_screen(void);
void title_screen(void);
void credits_screen(void);

UBYTE i = 0;
UBYTE j = 0;
UBYTE credits = 0;
PLAYER player;
WHITEFUR whiteFur;

LEVELID currentLvl = LEVEL1;
WORLDID currentWorld = WORLD1;
extern UBYTE finish;


void main(void)
{
	SWITCH_ROM_MBC5(2);
  kwakwa_screen();
	//disable_APA();
	credits = 0U;
	while(1)
	{
		title_screen();
		credits = 0U;
		reset_game();
		//disable_APA();
		while(credits == 0U)
		{

			game_screen();

		}
		//disable_APA();

		credits_screen();
		//disable_APA();
	}
}

#include <gb/gb.h>
#include <gb/drawing.h>

#include "game_screen.h"
#include "utils/reset_graphics.c"
#include "gbt_player.h"

UBYTE i;
UBYTE j;
UBYTE credits;
PLAYER player;
WHITEFUR whiteFur;

LEVELID currentLvl;
WORLDID currentWorld;
extern UBYTE finish;


void main()
{
	ENABLE_RAM_MBC1;
	SWITCH_ROM_MBC1(7);
    kwakwa_screen();
	//disable_APA();
	credits = 0U;
	while(1)
	{
		ENABLE_RAM_MBC1;
		SWITCH_ROM_MBC1(7);
		title_screen();
		credits = 0U;
		reset_game();
		//disable_APA();
		while(credits == 0U)
		{

			game_screen();

		}
		//disable_APA();
		ENABLE_RAM_MBC1;
		SWITCH_ROM_MBC1(7);
		credits_screen();
		disable_APA();
	}
}

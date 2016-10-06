#include <gb/gb.h>
#include "title_screen.h"
#include "kwakwa_screen.h"
#include "game_screen.h"
#include "utils/reset_graphics.c"


void main()
{
	/*ENABLE_RAM_MBC1;
	SWITCH_ROM_MBC1(7);
    kwakwa_screen();
	disable_APA();*/

	while(1)
	{
		/*ENABLE_RAM_MBC1;
		SWITCH_ROM_MBC1(7);
		title_screen();*/

		//disable_APA();

		game_screen();
	}
}

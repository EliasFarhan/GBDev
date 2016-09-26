#include <gb/gb.h>
#include "title_screen.h"
#include "kwakwa_screen.h"
#include "game_screen.h"
#include "utils/reset_graphics.c"


void main()
{

	//kwakwa_screen();
	//DISPLAY_OFF;
	//disable_APA();

	while(1)
	{
		//title_screen();
		//DISPLAY_OFF;
		//disable_APA();

		game_screen();
	}
}

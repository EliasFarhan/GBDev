#include <gb/gb.h>
#include <gb/drawing.h>

#include "title_screen.h"
#include "game_screen.h"



void main()
 {
	while(1)
	{
		
		title_screen();
		game_screen();
		//credits = 0U;
		//reset_game();
		//disable_APA();
		//while(credits == 0U)
		{
			//game_screen();
		}
		//disable_APA();

		//credits_screen();
		//disable_APA();
	}
}

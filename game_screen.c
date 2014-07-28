/*
 * game_screen.c
 *
 *  Created on: 28 juil. 2014
 *      Author: efarhan
 */

#include <gb/gb.h>
#include <gb/drawing.h>

void game_screen() NONBANKED
{

	gotogxy(5, 5);
	gprintf("GAME OVER");
	DISPLAY_ON;
	waitpad(J_A | J_B | J_START | J_SELECT);
	waitpadup();
	DISPLAY_OFF;
	DISABLE_RAM_MBC1;
}


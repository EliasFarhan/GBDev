/*
 * game_screen.c
 *
 *  Created on: 28 juil. 2014
 *      Author: efarhan
 */

#include <gb/gb.h>
#include <gb/drawing.h>
#include "game_screen.h"


#define MAX_SPRITES 1
#define SPRITE_SIZE 8

struct POS {
	UBYTE x;
	UBYTE y;
	UBYTE dir;//0 right, 1 left, 2 up, 3 down
};

unsigned char TileSprites[] =
{
		//Peanut idle
		0x00,0x00,0x00,0x00,0x07,0x07,0x0F,0x0F,
		  0x0F,0x0F,0x3F,0x3F,0xFF,0xFF,0x7E,0x7F,

		  0x18,0x1F,0x7E,0x63,0xFF,0x81,0xEF,0xF9,
		  0x9F,0xF1,0x7F,0x71,0x1F,0x1F,0x3C,0x3C,

		  0x78,0x78,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
		  0xFC,0xFC,0xF8,0xF8,0xE0,0xF0,0xC8,0x78,

		  0x00,0xF8,0x1E,0xF6,0x77,0xE9,0x37,0xEF,
		  0x39,0xEF,0x3E,0xE6,0xF8,0xF8,0x3C,0x3C,



};
unsigned char TileBackground[] =
{
		//Background
			0x45,0x10,0xFF,0x00,0xE7,0x10,0xCC,0x33,
			0x54,0x01,0xFF,0x00,0x7E,0x01,0xCC,0x33,
	//Brique
		0xFF,0xFF,0xFF,0x10,0x18,0xF7,0x18,0xF7,
		  0xFF,0xFF,0xFF,0x01,0x81,0x7F,0x81,0x7F


};

unsigned char BackgroundTileMap[] =
{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

UBYTE SpriteTileMap[] =
{
		//Peanut idle
	0,2,1,3,


};

UBYTE keys;
UBYTE finish;
struct POS player_pos;

enum AnimationState
{
	IDLE,
	WALK
};
void manage_input() NONBANKED
{

	if (keys & J_LEFT)
		if(player_pos.x != SPRITE_SIZE)
			player_pos.x--;

	if (keys & J_RIGHT)
		if(player_pos.x != 160-SPRITE_SIZE)
			player_pos.x++;

	if (keys & J_START)
		finish = 1;
}

void set_sprite() NONBANKED
{
	UBYTE i;
	for (i = 0; i != 4; i++)
	{
		set_sprite_tile( i, SpriteTileMap[i] );
	}
	move_sprite( 0, player_pos.x,    player_pos.y );
	move_sprite( 1, player_pos.x+8,   player_pos.y );
	move_sprite( 2, player_pos.x,    player_pos.y+8 );
	move_sprite( 3, player_pos.x+8,   player_pos.y+8 );


}

void game_screen() NONBANKED
{
	init_screen();

	finish = 0;
	while(!finish)
	{
		wait_vbl_done();
		keys = joypad();
		manage_input();
		set_sprite();
	}
	game_over();
}

void init_screen() NONBANKED
{
	UBYTE i,j;
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;
	set_sprite_data( 0, 4, TileSprites);

	set_bkg_data(0, 2, TileBackground);


	//Background
	for(i = 0; i != 18; i++)
		for(j = 0; j!= 20; j++)
			set_bkg_tiles(j,i,1,1, &BackgroundTileMap[i*20+j]);
	SPRITES_8x8;//TODO: why not 8x16?

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
	player_pos.x = 80+SPRITE_SIZE;
	player_pos.y = 144-SPRITE_SIZE;
	set_sprite();

}

void game_over() NONBANKED
{
	wait_vbl_done();
	HIDE_SPRITES;
	gotogxy(5, 5);
	gprintf("GAME OVER");

	DISPLAY_ON;
	waitpad(J_A | J_B | J_START | J_SELECT);
	waitpadup();
	DISPLAY_OFF;
	DISABLE_RAM_MBC1;
}

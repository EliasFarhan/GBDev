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
#define SPRITE_SIZE 16

struct POS {
	UBYTE x;
	UBYTE y;
};

unsigned char test_sprite[] =
{
  0x01,0x01,0x1E,0x1F,0x20,0x3F,0x4F,0x70,
  0x9F,0xE0,0xBF,0xC0,0xBF,0xC0,0xBF,0xC0,
  0x80,0x80,0x60,0xE0,0x10,0xF0,0xC8,0x38,
  0xE6,0x1E,0xF1,0x0F,0xFD,0x03,0xFD,0x03,
  0xBF,0xC0,0xBF,0xC0,0xBF,0xC0,0x9F,0xE0,
  0x4F,0x70,0x20,0x3F,0x1E,0x1F,0x01,0x01,
  0xFD,0x03,0xFD,0x03,0xF1,0x0F,0xE6,0x1E,
  0xC8,0x38,0x10,0xF0,0x60,0xE0,0x80,0x80
};

UBYTE sprite_tile[] =
{
	0, 1, 2, 3       /* direct North */

};

UBYTE keys;
struct POS player_pos;

void manage_input() NONBANKED
{
	if (keys & J_DOWN) {
		player_pos.y++;
	}
	if (keys & J_UP) {
		player_pos.y--;
	}
	if (keys & J_LEFT) {
		player_pos.x--;
	}
	if (keys & J_RIGHT) {
		player_pos.x++;
	}

}

void set_sprite() NONBANKED
{
	set_sprite_tile( 0, sprite_tile[0] );
	set_sprite_tile( 1, sprite_tile[1] );
	set_sprite_tile( 2, sprite_tile[2] );
	set_sprite_tile( 3, sprite_tile[3] );

	move_sprite( 0, player_pos.x+SPRITE_SIZE+8,    player_pos.y+SPRITE_SIZE+16 );
	move_sprite( 1, player_pos.x+SPRITE_SIZE+16,   player_pos.y+SPRITE_SIZE+16 );
	move_sprite( 2, player_pos.x+SPRITE_SIZE+8,    player_pos.y+SPRITE_SIZE+24 );
	move_sprite( 3, player_pos.x+SPRITE_SIZE+16,   player_pos.y+SPRITE_SIZE+24 );

}

void game_screen() NONBANKED
{
	init_screen();
	while(1)
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
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;
	set_sprite_data( 0, 4, test_sprite );
	SPRITES_8x8;

	//SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
	player_pos.x = 0;
	player_pos.y = 0;
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

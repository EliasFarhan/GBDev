/*
 * game_screen.c
 *
 *  Created on: 28 juil. 2014
 *      Author: efarhan
 */

#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/sample.h>
#include "game_screen.h"
#include "gbt_player.h"
#include "sound.h"
#include "physics.h"


#define PLAYER_SIZE 16U
#define GROUND_HEIGHT 8U

enum AnimationState
{
	IDLE,
	WALK,
	JUMP
};

struct PLAYER {
	Box box;
	enum AnimationState state;//0 right, 1 left, 2 up, 3 down
	UBYTE img_index; //for animations with more than one frame
	BYTE dir; //for walk and jump
	UBYTE timer; //for animations
	BYTE vely;//y-velocity for jump
	UBYTE hasJump;

};
extern const unsigned char * song_Data[];
unsigned char TileSprites[] =
{
	//PEANUT
	//IDLE
	  0x00,0x00,0x00,0x00,0x07,0x07,0x0F,0x0F,
	  0x0F,0x0F,0x3F,0x3F,0xFF,0xFF,0x7E,0x7F,

	  0x18,0x1F,0x7E,0x63,0xFF,0x81,0xEF,0xF9,
	  0x9F,0xF1,0x7F,0x71,0x1F,0x1F,0x3C,0x3C,

	  0x78,0x78,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
	  0xFC,0xFC,0xF8,0xF8,0xE0,0xF0,0xC8,0x78,

	  0x00,0xF8,0x1E,0xF6,0x77,0xE9,0x37,0xEF,
	  0x39,0xEF,0x3E,0xE6,0xF8,0xF8,0x3C,0x3C,
	//WALK1
	  0x00,0x00,0x00,0x00,0x03,0x03,0x07,0x07,
	  0x07,0x07,0x1F,0x1F,0x7F,0x7F,0x3F,0x3F,

	  0x0E,0x0F,0x3F,0x38,0x5F,0x70,0x7F,0x70,
	  0x9F,0xF0,0xBF,0xFC,0x73,0x73,0x60,0x60,

	  0x3C,0x3C,0x7E,0x7E,0xFE,0xFE,0xFE,0xFE,
	  0xFE,0xFE,0xFC,0xFC,0xF0,0xF8,0x64,0xBC,

	  0x00,0xFC,0xFC,0x7C,0xFA,0x0E,0xFA,0x0E,
	  0xFC,0x7C,0x92,0x72,0xFE,0xFE,0x0C,0x0C,
	//WALK2
	  0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,
	  0x03,0x03,0x0F,0x0F,0x3F,0x3F,0x1F,0x1F,

	  0x03,0x03,0x07,0x04,0x07,0x05,0x3F,0x39,
	  0x4F,0x79,0x4F,0x79,0x3F,0x3F,0x01,0x01,

	  0x1E,0x1E,0x3F,0x3F,0xFF,0xFF,0xFF,0xFF,
	  0xFF,0xFF,0xFE,0xFE,0xF8,0xFC,0xB2,0xDE,

	  0x80,0xFE,0xF0,0x7C,0xFC,0x0C,0xF4,0x1C,
	  0xF4,0xEC,0x38,0xE8,0xF8,0xF8,0xE0,0xE0,
	//WALK3
	  0x00,0x00,0x00,0x00,0x03,0x03,0x07,0x07,
	  0x07,0x07,0x1F,0x1F,0x7F,0x7F,0x3F,0x3F,

	  0x0F,0x0F,0x3F,0x30,0x5F,0x70,0x5F,0x70,
	  0xBF,0xFC,0x9F,0xF0,0x7F,0x7F,0x60,0x60,

	  0x3C,0x3C,0x7E,0x7E,0xFE,0xFE,0xFE,0xFE,
	  0xFE,0xFE,0xFC,0xFC,0xF0,0xF8,0x64,0xBC,

	  0x00,0xFC,0xC4,0xFC,0xFA,0x3E,0xEA,0x3E,
	  0xEC,0x3C,0xD2,0x72,0xFE,0xFE,0x0C,0x0C,
	//JUMP
	  0x00,0x00,0x00,0x00,0x07,0x07,0x0F,0x0F,
	  0x0F,0x0F,0x3F,0x3F,0xFF,0xFF,0x7E,0x7F,

	  0x18,0x1F,0x7E,0x63,0xFF,0x80,0xEF,0xF8,
	  0x9F,0xF0,0x7F,0x71,0x3F,0x3F,0x20,0x20,

	  0x78,0x78,0xFC,0xFC,0xFE,0xFE,0xFD,0xFF,
	  0xFD,0xFF,0xFB,0xFF,0xEF,0xF1,0xCF,0x79,

	  0xC6,0x7A,0x1C,0xF4,0xF8,0xE8,0xB8,0xE8,
	  0xBA,0xEA,0x7E,0xFE,0x8C,0x8C,0x00,0x00



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

unsigned char Background1TileMap[] =
{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

#define BOX1LENGTH 4
Box box1[BOX1LENGTH] =
{
	{16U,16U,32U,8U },
	{72U,64U,32U,16U},
	{8U,88U,32U,8U},
	{56U,112U, 32U,8U}
};

UBYTE SpriteTileMap[] =
{
		//Peanut idle
	0,2,1,3,
	//Peanut walk
	4,6,5,7,
	8,10,9,11,
	12,14,13,15,
	8,10,9,11,
	//Peanut jump
	16,18,17,19,


};

UBYTE keys;
UBYTE finish;
struct PLAYER player;


void manage_input() NONBANKED
{

	if(keys & J_A)
	{
		if(!player.hasJump && player.state != JUMP)
		{
			player.state = JUMP;
			player.timer = 0;
			player.img_index = 0;
			player.vely = -4;
			play_sound( SOUND_SHOOTING );
			player.hasJump = 1U;
		}
	}else{
		player.hasJump = 0U;
	}

	if( keys & J_B)
	{
		//gbt_play(song_Data, 2, 7);
		//gbt_loop(0);
	}

	if (keys & J_LEFT)
	{
		if(player.box.x != 0U)
		{
			player.box.x--;
			player.dir = -1;
			if(player.state == IDLE)
			{
				player.state = WALK;
			}
		}
	}
	else if (keys & J_RIGHT)
	{
		if(player.box.x != 160U)
		{
			player.box.x++;
			player.dir = 1;
			if(player.state == IDLE)
			{
				player.state = WALK;
			}
		}
	}
	else
	{
		if(player.state != JUMP)
		{
			player.state = IDLE;
			player.timer = 0;
			player.img_index = 0;
		}
	}
	if (keys & J_START)
	{
		finish = 1;
	}
}

void set_sprite() NONBANKED
{
	UBYTE i;
	UBYTE origin_index;
	if(player.state == IDLE)
	{
		origin_index = 0U;
	}
	else if(player.state == WALK)
	{
		origin_index = (player.img_index+1U)*4U;
	}
	else if(player.state == JUMP)
	{
		origin_index = 20U;
	}

	for (i = origin_index; i != origin_index+4; i++)
	{
		set_sprite_tile( i-origin_index, SpriteTileMap[i] );
	}

	if(player.dir == 1)
	{
		for(i = 0;i!=4;i++)
		{
			set_sprite_prop(i,0x00U);
		}
		move_sprite( 0, player.box.x+8U,    player.box.y );
		move_sprite( 1, player.box.x+16U,   player.box.y );
		move_sprite( 2, player.box.x+8U,    player.box.y+8 );
		move_sprite( 3, player.box.x+16U,   player.box.y+8 );
	}
	else if(player.dir == -1)
	{
		for(i = 0;i!=4;i++)
		{
			set_sprite_prop(i,S_FLIPX);
		}
		move_sprite( 1, player.box.x+8U,    player.box.y );
		move_sprite( 0, player.box.x+16U,   player.box.y );
		move_sprite( 3, player.box.x+8U,    player.box.y+8 );
		move_sprite( 2, player.box.x+16U,   player.box.y+8 );

	}


}
void manage_animation() NONBANKED
{
	if(player.state == WALK)
	{
		player.timer++;
		if(player.timer == 5)
			player.img_index++;
		else if(player.timer == 10)
			player.img_index++;
		else if(player.timer == 15)
			player.img_index++;
		else if(player.timer == 20)
		{
			player.timer =0;
			player.img_index = 0;
		}



	}
}
void manage_physics() NONBANKED
{
	UBYTE i;

	if(player.state == JUMP)
	{
		player.timer ++;
		if(player.timer == 5U)
		{
			player.vely += 1U;


			player.timer = 0;
		}
		player.box.y += player.vely;



		for(i = 0; i<BOX1LENGTH;i++)
		{
			if(checkCollision(&(player.box), &(box1[i])))
			{

				if(player.box.y<box1[i].y)
				{
					player.box.y = box1[i].y-box1[i].h;
					player.state = IDLE;
					return;
				}
				else
				{
					player.box.y = box1[i].y+PLAYER_SIZE;
					if(player.vely < 0U)
						player.vely = 1;
				}
			}


		}


		if(player.box.y > 144U-GROUND_HEIGHT-1U)
		{
			player.box.y = 144U-GROUND_HEIGHT;
			player.state = IDLE;
			return;
		}
	}
	else if(player.state == IDLE || player.state == WALK)
	{
		UBYTE foot;
		Box tmp_box;
		tmp_box.x = player.box.x;
		tmp_box.y = player.box.y+1;
		tmp_box.w = player.box.w;
		tmp_box.h = player.box.h;
		foot = 0;
		for(i = 0; i<BOX1LENGTH;i++)
		{
			if(checkCollision(&(tmp_box),  &(box1[i])) || player.box.y == 144U-GROUND_HEIGHT)
			{
				foot++;
			}

		}
		if(foot == 0)
		{
			player.state = JUMP;
			if(player.vely < 0U)
				player.vely = 1;
		}
	}
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
		manage_animation();
		manage_physics();
		set_sprite();

		gbt_update();
		tick_sound();

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
	init_sounds();

	set_sprite_data( 0, 20, TileSprites);


	set_bkg_data(0, 2, TileBackground);


	//Background
	for(i = 0; i != 18; i++)
		for(j = 0; j!= 20; j++)
			set_bkg_tiles(j,i,1,1, &Background1TileMap[i*20+j]);
	SPRITES_8x8;//TODO: why not 8x16?

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
	player.box.x = 8U;
	player.box.y = 144U-GROUND_HEIGHT;
	player.box.w = PLAYER_SIZE;
	player.box.h = PLAYER_SIZE;
	player.dir = 1;
	player.img_index = 0;
	player.state = IDLE;
	player.timer = 0;//for animation purpose and physics
	player.vely = 0;
	player.hasJump = 0U;
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

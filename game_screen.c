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
#include "data/peanut.h"

//include all the levels
#include "levels/level1.h"


#define PLAYER_SIZE 16U
#define GROUND_HEIGHT 8U

enum AnimationState
{
	IDLE,
	WALK,
	JUMP,
	CROUCH,
	CROUCHWALK
};

typedef struct
{
	void* init_level;//function
	void* manage_physics;//function
} Level;

typedef struct
{
	UBYTE x;
	UBYTE y;
	UBYTE w;
	UBYTE h;
} Box;

typedef struct{
	Box box;
	enum AnimationState state;//0 right, 1 left, 2 up, 3 down
	UBYTE img_index; //for animations with more than one frame
	BYTE dir; //for walk and jump
	UBYTE timer; //for animations
	BYTE vely;//y-velocity for jump
	UBYTE hasJump;

} PLAYER;
extern const unsigned char * song_Data[];
extern unsigned char TilePeanut[];
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

UBYTE PeanutTileMap[] =
{
		//Peanut idle
	0U, 2U, 1U, 3U,
	//Peanut walk
	4U, 6U, 5U, 7U,
	8U, 10U,9U, 11U,
	12U,14U,13U,15U,
	8U, 10U,9U, 11U,
	//Peanut jump
	16U,18U,17U,19U,
	//Peanut crouch
	20U,22U,21U,23U,
	24U,26U,25U,27U,
	28U,30U,29U,31U,
	24U,26U,25U,27U,



};

UBYTE keys;
UBYTE finish;
PLAYER player;

Level levels[] = {
		{(void*)init_lvl1, (void*)manage_physics_lvl1}
};

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

	if(player.state != JUMP)
	{
		if (keys & J_B)
		{
			player.state = CROUCH;


		}
		else
		{
			player.state = IDLE;
		}
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
			if(player.state == CROUCH)
			{
				player.state = CROUCHWALK;
			}
		}
	}
	else if (keys & J_RIGHT)
	{
		if(player.box.x != 160U-PLAYER_SIZE)
		{
			player.box.x++;
			player.dir = 1;
			if(player.state == IDLE)
			{
				player.state = WALK;
			}
			if(player.state == CROUCH)
			{
				player.state = CROUCHWALK;
			}
		}
	}
	else
	{
		if(player.state == JUMP)
		{
			player.img_index = 0;
		}
		if(player.state == WALK)
		{
			player.state = IDLE;
			player.timer = 0;
			player.img_index = 0;
		}
		if(player.state == CROUCHWALK)
		{
			player.state = CROUCH;
			player.timer = 0;
			player.img_index = 0;
		}
	}
	if (keys & J_START)
	{
		finish = 1;
	}
}
char checkCollision(Box* a, Box* b) NONBANKED
{
	return !(b->x > a->x+a->w ||
			b->x+b->w < a->x ||
			b->y < a->y-a->h ||
			b->y-b->h > a->y);
}
void set_sprites() NONBANKED
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
	else if(player.state == CROUCH)
	{
		origin_index = 24U;
	}
	else if(player.state == CROUCHWALK)
	{
		origin_index = (player.img_index+6U)*4U;
	}
	for (i = origin_index; i != origin_index+4; i++)
	{
		set_sprite_tile( i-origin_index, PeanutTileMap[i] );
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
	if(player.state == WALK || player.state == CROUCHWALK)
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
					player.timer = 0U;
					player.img_index = 0U;
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
			player.timer = 0U;
			player.img_index = 0U;
			return;
		}
	}
	else if(player.state == IDLE || player.state == WALK || player.state == CROUCH || player.state == CROUCHWALK)
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
		set_sprites();

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

	set_sprite_data( 0U, 36U, TilePeanut);


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
	set_sprites();

}

void init_level()
{

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

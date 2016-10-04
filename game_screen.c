/*
 * game_screen.c
 *
 *  Created on: 28 juil. 2014
 *      Author: efarhan
 */

#include <gb/gb.h>
#include <gb/drawing.h>
//#include <gb/sample.h>
#include "game_screen.h"
//#include "gbt_player.h"
#include "sound.h"

#include "box_collision.h"


//include all the levels



#define PLAYER_SIZE 16U
#define GROUND_HEIGHT 8U



extern unsigned char * song_Data[];





extern UBYTE PeanutTileMap[];


UBYTE keys;
UBYTE finish;
PLAYER player;

extern Level lvl1;
extern Level lvl2;

Level* levels[2] = {
		&lvl1,
		&lvl2
};

LEVELID currentLvl;

extern unsigned char TilePeanut[] NONBANKED;
extern unsigned char TileEnvironment[];

extern UBYTE TileEnvironmentLength;
extern unsigned char TileBackground[];
extern unsigned char TileWhite[];
extern UBYTE TileBackgroundLength;
extern unsigned char TileWhalePoster[];
extern UBYTE TileWhalePosterLength;

void manage_physics_lvl1(PLAYER* player) NONBANKED;
void manage_physics_lvl2(PLAYER* player) NONBANKED;

void manage_input() NONBANKED
{
	if(!(player.booleanState & TRANSITIONNING))
	{
		if(keys & J_A)
		{
			if((!player.booleanState & HASJUMP) && player.state != JUMP)
			{
				player.state = JUMP;
				player.timer = 0;
				player.img_index = 0;
				player.vely = -4;

				play_sound( SOUND_SHOOTING );
				player.booleanState = player.booleanState | HASJUMP;
			}
		}else{
			player.booleanState = player.booleanState & ~HASJUMP;
		}

		if(player.state != JUMP)
		{
			if (keys & J_B)
			{
				if(player.state != WALK)
					player.state = CROUCH;
				else
				{
					player.timer = 0U;
					player.img_index = 0U;
					player.state = CROUCHWALK;
				}


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


				if(player.state == IDLE)
				{
					player.state = WALK;
				}
				if(player.state == CROUCH)
				{
					player.state = CROUCHWALK;
				}
				if(!(player.state == CROUCHWALK && player.timer % 2U == 1U))
				{
					player.box.x--;
				}
				player.dir = -1;
			}
		}
		else if (keys & J_RIGHT)
		{
			if(player.box.x != 160U-PLAYER_SIZE)
			{

				if(player.state == IDLE)
				{
					player.state = WALK;
				}
				if(player.state == CROUCH)
				{
					player.state = CROUCHWALK;
				}
				if(!(player.state == CROUCHWALK && player.timer % 2U == 1U))
				{
					player.box.x++;
				}
				player.dir = 1;
			}
		}
		else
		{
			if(player.state == IDLE)
			{
				player.timer = 0;
				player.img_index = 0;
			}
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
			//finish = 1;
		}
	}
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
	else if(player.state == CROUCHTRANSITIONIN)
	{
		origin_index = (player.img_index+8U)*4U;
	}
	else if(player.state == CROUCHTRANSITIONOUT)
	{
		origin_index = (player.img_index+12U)*4U;
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
	if(player.state == WALK || player.state == CROUCHTRANSITIONIN || player.state == CROUCHTRANSITIONOUT)
	{
		player.timer++;
		if(player.booleanState & TRANSITIONNING && player.timer % 2U == 1)
		{
			player.box.x += player.dir;
		}

		if(player.timer == 5U)
			player.img_index++;
		else if(player.timer == 10U)
			player.img_index++;
		else if(player.timer == 15U)
			player.img_index++;
		else if(player.timer == 20U)
		{
			if(player.state == CROUCHTRANSITIONIN)
			{
				player.state = CROUCHTRANSITIONOUT;
				player.box.x = player.newX;
				player.box.y = player.newY;
				switch_to_level(player.nextLevel);
			}
			else if(player.state == CROUCHTRANSITIONOUT)
			{
				player.state = IDLE;
				player.booleanState = player.booleanState & ~TRANSITIONNING;
			}
			player.timer =0U;
			player.img_index = 0U;
		}



	}
	else if(player.state == CROUCHWALK)
	{
		player.timer++;
		if(player.timer == 5U)
			player.img_index++;
		else if(player.timer == 10U)
		{
			player.timer = 0U;
			player.img_index = 0U;
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



		for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
		{
			if(checkCollision(&(player.box), &(levels[currentLvl]->boxes[i])))
			{

				if(player.box.y<levels[currentLvl]->boxes[i].y)
				{
					player.box.y = levels[currentLvl]->boxes[i].y-levels[currentLvl]->boxes[i].h;
					player.state = IDLE;
					player.timer = 0U;
					player.img_index = 0U;
					return;
				}
				else
				{
					player.box.y = levels[currentLvl]->boxes[i].y+PLAYER_SIZE;
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
		for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
		{
			if(checkCollision(&(tmp_box),  &(levels[currentLvl]->boxes[i])) || player.box.y == 144U-GROUND_HEIGHT)
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
	if(currentLvl ==LEVEL1)
	{
		manage_physics_lvl1(&player);

	} else if(currentLvl ==LEVEL2)
	{
		manage_physics_lvl2(&player);

	}

}
void switch_to_level(LEVELID levelID) NONBANKED
{
	UBYTE i,j;

	play_sound( SOUND_EXPLOSION );
	currentLvl = levelID;
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	for(i = 0; i != 18; i++)
	{
		for(j = 0; j!= 20; j++)
		{
			set_bkg_tiles(j,i,1,1, &(levels[currentLvl]->LvlTileMap)[i*20+j]);
		}
	}
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
}
void game_screen() NONBANKED
{

	currentLvl = LEVEL1;
	init_screen();

	finish = 0U;
	while(!finish)
	{
		wait_vbl_done();
		keys = joypad();
		manage_input();
		manage_animation();
		manage_physics();
		set_sprites();

		//gbt_update();

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
	set_sprite_data( 0U, 0x40U, TilePeanut);


	set_bkg_data(0, 1, TileWhite);
	set_bkg_data(1U, TileEnvironmentLength, TileEnvironment);
	set_bkg_data(TileEnvironmentLength+1U, TileBackgroundLength, TileBackground);
	set_bkg_data(TileBackgroundLength+TileEnvironmentLength+1U, TileWhalePosterLength, TileWhalePoster);

	//Background
	for(i = 0; i != 18; i++)
	{
		for(j = 0; j!= 20; j++)
		{

			set_bkg_tiles(j,i,1,1, &(levels[currentLvl]->LvlTileMap)[i*20+j]);
		}
	}
	SPRITES_8x8;//TODO: why not 8x16?

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
	player.booleanState = 0x00;
	player.box.x = 8U;
	player.box.y = 144U-GROUND_HEIGHT;
	player.box.w = PLAYER_SIZE;
	player.box.h = PLAYER_SIZE;
	player.dir = 1;
	player.img_index = 0;
	player.state = IDLE;
	player.timer = 0;//for animation purpose and physics
	player.vely = 0;


	set_sprites();

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
}

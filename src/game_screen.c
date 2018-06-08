/*
 * game_screen.c
 *
 *  Created on: 28 juil. 2014
 *      Author: efarhan
 */

#include <gb/gb.h>
#include "game_screen.h"
#include "gbt_player.h"
#include "sound.h"

#include "box_collision.h"


extern unsigned char * song_Data[];
extern unsigned char * victory_song_Data[];
extern UBYTE tilemap_peanut[];
extern unsigned char press_start_tiledata[];
extern unsigned char press_start_tilemap[];

UBYTE keys;
UBYTE finish;
extern PLAYER player;

extern Level lvl1;
extern Level lvl2;
extern Level lvl3;
extern Level lvl4;
extern Level lvl5;
extern Level lvl6;
extern Level lvl10;
extern Level lvl13;

Level* levels[15] = {
		&lvl1,
		&lvl2,
		&lvl3,
		&lvl4,
		&lvl5,
		&lvl6,
		NULL,
		NULL,
		NULL,
		&lvl10,
		NULL,
		NULL,
		&lvl13,
		NULL,
		NULL
};

World worlds[] = {
		{LEVEL6},
		{LEVEL11}
};
extern WORLDID currentWorld;
extern LEVELID currentLvl;

extern unsigned char tile_peanut[];
extern unsigned char tile_whitefur[];
extern unsigned char tile_seagull[];
extern unsigned char tile_guard[];
extern unsigned char tile_environment[];
extern unsigned char tilemap_seagull[];
UBYTE TileEnvironmentLength = 10U;
extern unsigned char tile_background[];
extern unsigned char tile_white[];
UBYTE TileBackgroundLength = 8U;
extern unsigned char tile_whale_poster[];
UBYTE TileWhalePosterLength = 48U;
extern UBYTE i, j;
extern WHITEFUR whiteFur;

void manage_physics();

void reset_lvl1();
void reset_lvl2();
void reset_lvl3();
void reset_lvl4();
void reset_lvl5();
void reset_lvl6();
void reset_lvl10();
void reset_lvl13();

void manage_input() NONBANKED
{

	if(!(player.booleanState & TRANSITIONNING)
			&& !(player.booleanState & HASGAMEOVER)
			&& !(player.booleanState & HASVICTORY)
			&& !(player.booleanState & WORLD_SWITCH))
	{
		if(keys & J_A)
		{
			if((!player.booleanState & HASJUMP) &&
					player.state != JUMP &&
					player.state != CLIMB &&
					player.state != JUMPCLIMB &&
					player.state != CLIMBWALK)
			{
				player.state = JUMP;
				player.timer = 0;
				player.img_index = 0;
				player.vely = -4;

				play_sound( SOUND_JUMP );
				player.booleanState = player.booleanState | HASJUMP;
			}
		}
		else
		{
			player.booleanState = player.booleanState & ~HASJUMP;
		}
		if (keys & J_B)
		{
			if(player.key != NULL)
			{

			}
			else if(player.state != JUMPCLIMB && player.state != CLIMB && player.state != CLIMBWALK)
			{
				if(player.state != JUMP)
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
					player.state = JUMPCLIMB;
					player.img_index = 0U;
				}
			}
		}
		else
		{
			if(player.state == JUMPCLIMB || player.state == CLIMB || player.state == CLIMBWALK)
			{
				player.state = JUMP;
				player.vely = 1U;
				player.timer = 0U;

			}
			else if(player.state == CROUCH)
			{
				player.state = IDLE;
			}
			else if(player.state == CROUCHWALK)
			{
				player.state = WALK;
			}
		}



		if (keys & J_LEFT)
		{
			if(player.state != CLIMB && player.state != CLIMBWALK)
			{
				if(player.box.x != 8U)
				{


					if(player.state == IDLE)
					{
						player.state = WALK;
					}
					if(player.state == CROUCH)
					{
						player.state = CROUCHWALK;
					}
					if(player.state != WALK && player.state != CROUCHWALK)
					{
						player.box.x--;
					}
					player.dirX = -1;
				}
			}
		}
		else if (keys & J_RIGHT)
		{
			if(player.state != CLIMB && player.state != CLIMBWALK)
						{
			if(player.box.x != 160U-PLAYER_SIZE-8U)
			{

				if(player.state == IDLE)
				{
					player.state = WALK;
				}
				if(player.state == CROUCH)
				{
					player.state = CROUCHWALK;
				}
				if(player.state != WALK && player.state != CROUCHWALK)
				{
					player.box.x++;
				}
				player.dirX = 1;
			}}
		}
		else
		{
			if(player.state == IDLE)
			{
				player.timer = 0;
				player.img_index = 0;
			}
			if(player.state == JUMP || player.state == JUMPCLIMB)
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
		if (keys & J_DOWN)
		{
			if(player.state == CLIMB)
			{
				player.dirY = 1;
				player.state = CLIMBWALK;
			}
		}
		else if(keys & J_UP)
		{
			if(player.state == CLIMB)
			{
				player.dirY = -1;
				player.state = CLIMBWALK;
			}
		}
		else
		{
			if(player.state == CLIMBWALK)
			{
				player.state = CLIMB;
			}
		}

		if (keys & J_START)
		{
			//finish = 1;
		}
	}
	else if(player.booleanState & HASVICTORY)
	{
		if(keys & J_A || keys & J_B || keys & J_START)
		{
			finish = 1U;
			currentLvl = LEVEL6;
			gbt_stop();
		}
	}
	else if(player.booleanState & WORLD_SWITCH)
	{
		if (keys & J_LEFT)
		{

			player.dirX = -1;
		}
		else if (keys & J_RIGHT)
		{

			player.dirX = 1;
		}
		else
		{
			player.dirX = 1;
		}
	}
}

UBYTE previous_sprite_index;

void manage_doggy_sprites(UBYTE sprite_index)
{
	UBYTE origin_index;
	//SWITCH_ROM_MBC1(6);
	origin_index = levels[currentLvl]->doggy->img_index << 4U;
	for(i = 0U; i != 16U; i++)
	{
		set_sprite_tile(sprite_index+i , DOG_INDEX + origin_index + i );
	}
	if(levels[currentLvl]->doggy->dirX == -1)
	{
		for(i = 0U; i != 16U ;i++)
		{
			set_sprite_prop(sprite_index+i,0x00U);
		}
		move_sprite( sprite_index+0U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+1U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y-16U+8U);
		move_sprite( sprite_index+2U, levels[currentLvl]->doggy->box.x+8U+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+3U, levels[currentLvl]->doggy->box.x+8U+8U,  levels[currentLvl]->doggy->box.y-16U+8U);

		move_sprite( sprite_index+4U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+5U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y+8U);
		move_sprite( sprite_index+6U, levels[currentLvl]->doggy->box.x+8U+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+7U, levels[currentLvl]->doggy->box.x+8U+8U, levels[currentLvl]->doggy->box.y+8U);

		move_sprite( sprite_index+8U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+9U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y-16U+8U);
		move_sprite( sprite_index+10U, levels[currentLvl]->doggy->box.x+24U+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+11U, levels[currentLvl]->doggy->box.x+24U+8U,  levels[currentLvl]->doggy->box.y-16U+8U);

		move_sprite( sprite_index+12U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+13U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y+8U);
		move_sprite( sprite_index+14U, levels[currentLvl]->doggy->box.x+24U+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+15U, levels[currentLvl]->doggy->box.x+24U+8U, levels[currentLvl]->doggy->box.y+8U);
	}
	else
	{
		for(i = 0U; i != 16U ;i++)
		{
			set_sprite_prop(sprite_index+i,S_FLIPX);
		}
		move_sprite( sprite_index+10U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+11U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y-16U+8U);
		move_sprite( sprite_index+8U, levels[currentLvl]->doggy->box.x+8U+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+9U, levels[currentLvl]->doggy->box.x+8U+8U,  levels[currentLvl]->doggy->box.y-16U+8U);

		move_sprite( sprite_index+14U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+15U, levels[currentLvl]->doggy->box.x+8U, levels[currentLvl]->doggy->box.y+8U);
		move_sprite( sprite_index+12U, levels[currentLvl]->doggy->box.x+8U+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+13U, levels[currentLvl]->doggy->box.x+8U+8U, levels[currentLvl]->doggy->box.y+8U);

		move_sprite( sprite_index+2U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+3U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y-16U+8U);
		move_sprite( sprite_index+0U, levels[currentLvl]->doggy->box.x+24U+8U, levels[currentLvl]->doggy->box.y-24U+8U);
		move_sprite( sprite_index+1U, levels[currentLvl]->doggy->box.x+24U+8U,  levels[currentLvl]->doggy->box.y-16U+8U);

		move_sprite( sprite_index+6U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+7U, levels[currentLvl]->doggy->box.x+16U+8U, levels[currentLvl]->doggy->box.y+8U);
		move_sprite( sprite_index+4U, levels[currentLvl]->doggy->box.x+24U+8U, levels[currentLvl]->doggy->box.y-8U+8U);
		move_sprite( sprite_index+5U, levels[currentLvl]->doggy->box.x+24U+8U, levels[currentLvl]->doggy->box.y+8U);
	}
}

void manage_player_sprites()
{
	//PLAYER POSITION MANAGEMENT
	if(player.state != CLIMB && player.state != CLIMBWALK)
	{
		if(player.dirX == 1)
		{
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(i,0x00U);
			}
			move_sprite( 0U, player.box.x+8U,    player.box.y );
			move_sprite( 1U, player.box.x+16U,   player.box.y );
			move_sprite( 2U, player.box.x+8U,    player.box.y+8 );
			move_sprite( 3U, player.box.x+16U,   player.box.y+8 );
		}
		else if(player.dirX == -1)
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
	else //CLIMBING
	{
		if(player.dirY == 1 && player.dirX == 1)
		{
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(i,S_FLIPY);
			}
			move_sprite( 2, player.box.x+8U,    player.box.y );
			move_sprite( 3, player.box.x+16U,   player.box.y );
			move_sprite( 0, player.box.x+8U,    player.box.y+8 );
			move_sprite( 1, player.box.x+16U,   player.box.y+8 );
		}
		else if(player.dirY == -1&& player.dirX == 1)
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
		else if(player.dirY == -1&& player.dirX == -1)
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
		else if(player.dirY == 1 && player.dirX == -1)
		{
			move_sprite( 3, player.box.x+8U,    player.box.y );
			move_sprite( 2, player.box.x+16U,   player.box.y );
			move_sprite( 1, player.box.x+8U,    player.box.y+8 );
			move_sprite( 0, player.box.x+16U,   player.box.y+8 );
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(i, S_FLIPX|S_FLIPY);
			}

		}
	}
}
void set_sprites() NONBANKED
{

	UBYTE origin_index;
	UBYTE sprite_index;
	KEY* key;
	key = NULL;
	sprite_index = 0U;

	if((player.booleanState & HASVICTORY)||
			(player.booleanState & WORLD_SWITCH))
	{
		origin_index = 104U;
	}
	else if(player.state == IDLE)
	{
		if(player.key != NULL)
		{
			origin_index = 80U;
		}
		else
		{
			origin_index = 0U;
		}
	}
	else if(player.state == WALK)
	{
		if(player.key != NULL)
		{
			origin_index = (player.img_index+21U)<<2U;
		}else{
			origin_index = (player.img_index+1U)<<2U;
		}
	}
	else if(player.state == JUMP)
	{

		if(player.key != NULL)
			origin_index = 100U;
		else
			origin_index = 20U;
	}
	else if(player.state == CROUCH)
	{
		origin_index = 24U;
	}
	else if(player.state == CROUCHWALK)
	{
		origin_index = (player.img_index+6U)<<2U;
	}
	else if(player.state == CROUCHTRANSITIONIN)
	{
		origin_index = (player.img_index+8U)<<2U;
	}
	else if(player.state == CROUCHTRANSITIONOUT)
	{
		origin_index = (player.img_index+12U)<<2U;
	}
	else if(player.state == CLIMB || player.state == CLIMBWALK)
	{
		origin_index = (player.img_index+16U)<<2U;
	}
	else if(player.state == JUMPCLIMB)
	{
		origin_index = 72U;
	}
	else if(player.state == DEAD)
	{
		origin_index = 76U;
	}

	SWITCH_ROM_MBC1(5);
	for (i = origin_index; i != origin_index+4; i++)
	{
		set_sprite_tile( i-origin_index, tilemap_peanut[i] );
		sprite_index++;
	}
	//SHOW WHITEFUR
	if(currentLvl == LEVEL6 || currentLvl == LEVEL13)
	{


		for (i = 0U; i != 8U; i++)
		{
			if(player.booleanState & HASVICTORY)
			{
				set_sprite_tile( i+sprite_index, WF_INDEX+i+12U );
			}
			else if(player.booleanState & WORLD_SWITCH)
			{
				if(i >=4U)
				{
					set_sprite_tile( i+sprite_index, WF_INDEX+i+16U+(whiteFur.img_index<<2U) );
				}
				else
				{
					set_sprite_tile( i+sprite_index, WF_INDEX+i+12U );
				}
			}
			else
			{
				if(whiteFur.timer >= 10U && i >=4U)
				{
					set_sprite_tile( i+sprite_index, WF_INDEX+i+4U );
				}
				else
				{
					set_sprite_tile( i+sprite_index, WF_INDEX+i );
				}
			}


			set_sprite_prop(sprite_index+i,0x00U);
		}
		move_sprite( sprite_index+0, whiteFur.posX,    120U);
		move_sprite( sprite_index+1, whiteFur.posX,    120U+8U);
		move_sprite( sprite_index+2, whiteFur.posX+8U, 120U);
		move_sprite( sprite_index+3, whiteFur.posX+8U, 120U+8U);
		move_sprite( sprite_index+4, whiteFur.posX,    136U);
		move_sprite( sprite_index+5, whiteFur.posX,    136U+8U);
		move_sprite( sprite_index+6, whiteFur.posX+8U, 136U);
		move_sprite( sprite_index+7, whiteFur.posX+8U, 136U+8U);
		sprite_index+=8U;
	}
	//MOVE TEXT SPRITES
	if(player.booleanState & HASGAMEOVER)
	{
		SWITCH_ROM_MBC1(5);
		for(i = 0; i != 8; i++)
		{
			set_sprite_prop(sprite_index+i,0x00U);
			set_sprite_tile(sprite_index + i, STR_INDEX+press_start_tilemap[GAME_OVER_INDEX+i]);
			if(i>=4)
			{
				move_sprite(sprite_index+i, 48U+(i<<3)+8U,40U);
			}
			else
			{
				move_sprite(sprite_index+i, 48U+(i<<3),40U);
			}
			set_sprite_prop(sprite_index+i,0x00U);
		}
		sprite_index += 8U;
	}
	// SHOW VICTORY TEXT
	else if(player.booleanState & HASVICTORY)
	{

		SWITCH_ROM_MBC1(5);
		for(i = 0; i != 7; i++)
		{
			set_sprite_prop(sprite_index+i,0x00U);
			set_sprite_tile(sprite_index +i, STR_INDEX+press_start_tilemap[VICTORY_INDEX+i]);

			move_sprite(sprite_index+i, 54U+(i<<3),108U);
			set_sprite_prop(sprite_index+i,0x00U);
		}
		sprite_index += 7U;

	}
	//SHOW SEAGULL ENEMIES

	SWITCH_ROM_MBC1(6);
	if(levels[currentLvl]->enemy != NULL && !(levels[currentLvl]->enemy->dead && levels[currentLvl]->enemy->timer == DEAD_SEAGULL_TIME))
	{
		if(levels[currentLvl]->enemy->dead)
		{
			origin_index = 0xCU;

		}
		else
		{
			origin_index = levels[currentLvl]->enemy->img_index<<2;
		}
		for(i = 0U; i != 4U; i++)
		{
			set_sprite_tile( i+sprite_index, SEA_INDEX+i+origin_index );
		}
		if(levels[currentLvl]->enemy->dirX == 1)
		{
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(sprite_index+i,0x00U);
			}
			move_sprite( sprite_index+0U, levels[currentLvl]->enemy->box.x+8U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+2U, levels[currentLvl]->enemy->box.x+8U+8U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+1U, levels[currentLvl]->enemy->box.x+8U,  levels[currentLvl]->enemy->box.y+8U);
			move_sprite( sprite_index+3U, levels[currentLvl]->enemy->box.x+8U+8U, levels[currentLvl]->enemy->box.y+8U);
		}
		else
		{
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(sprite_index+i,S_FLIPX);
			}
			move_sprite( sprite_index+2U, levels[currentLvl]->enemy->box.x+8U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+0U, levels[currentLvl]->enemy->box.x+8U+8U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+3U, levels[currentLvl]->enemy->box.x+8U,  levels[currentLvl]->enemy->box.y+8U);
			move_sprite( sprite_index+1U, levels[currentLvl]->enemy->box.x+8U+8U, levels[currentLvl]->enemy->box.y+8U);
		}
		sprite_index+=4U;
	}

	//DOGGY
	if(levels[currentLvl]->doggy != NULL)
	{

		SWITCH_ROM_MBC1(7);
		manage_doggy_sprites(sprite_index);
		sprite_index += 16U;

	}

	//SHOW KEY LOCK
	if(levels[currentLvl]->lock != NULL && levels[currentLvl]->lock->locked)
	{
		UBYTE height;
		height = 2U;
		if(levels[currentLvl]->lock->box->h >= 48U)
		{
			height = 4U;
		}

		for(i = 0; i != height; i++)
		{
			set_sprite_prop(sprite_index+i,0x00U);
			set_sprite_tile( i+sprite_index, ENV_INDEX+8U );
			if(i < height>>1)
			{
			move_sprite(i+sprite_index,levels[currentLvl]->lock->box->x+8U,levels[currentLvl]->lock->box->y-(i<<3)+8U);
			}
			else
			{
				move_sprite(i+sprite_index,levels[currentLvl]->lock->box->x+8U,levels[currentLvl]->lock->box->y-(i<<3)+8U-16U);
			}
		}
		sprite_index += height;
		for(i = 0; i != 4; i++)
		{
			set_sprite_prop(sprite_index+i,0x00U);
			set_sprite_tile( i+sprite_index, ENV_INDEX+4U+i );
		}
		move_sprite( sprite_index+0, levels[currentLvl]->lock->box->x+4U, levels[currentLvl]->lock->box->y-(8U<<(height>>2) ));
		move_sprite( sprite_index+2, levels[currentLvl]->lock->box->x+12U, levels[currentLvl]->lock->box->y -(8U<<(height>>2)));
		move_sprite( sprite_index+1, levels[currentLvl]->lock->box->x+4U,  levels[currentLvl]->lock->box->y+8U -(8U<<(height>>2) ));
		move_sprite( sprite_index+3, levels[currentLvl]->lock->box->x+12U, levels[currentLvl]->lock->box->y+8U -(8U<<(height>>2) ));
		sprite_index+=4U;
	}
	//SHOW WALL
	if(levels[currentLvl]->wall != NULL)
	{
		const UBYTE height = levels[currentLvl]->wall->box->h>>3;
		for(i = 0; i != height; i++)
		{
			set_sprite_prop(sprite_index+i,0x00U);
			set_sprite_tile( i+sprite_index, ENV_INDEX+8U );
			move_sprite(i+sprite_index,levels[currentLvl]->wall->box->x+8U,levels[currentLvl]->wall->box->y-(i<<3)+8U);

		}
		sprite_index+=height;
	}
	//SHOW KEYS


	if(player.key != NULL)
	{
		key = player.key;
	}

	if(levels[currentLvl]->key != NULL && !levels[currentLvl]->key->used)
	{
		key = levels[currentLvl]->key;
	}

	if(key != NULL)
	{
		SWITCH_ROM_MBC1(6);
		for(i = 0; i != 4; i++)
		{
			set_sprite_prop(i+sprite_index,0x00U);

			set_sprite_tile( i+sprite_index, ENV_INDEX+i );

		}
		//MOVE SPRITES
		move_sprite( sprite_index+0, key->box.x+8U, key->box.y);
		move_sprite( sprite_index+2, key->box.x+16U, key->box.y);
		move_sprite( sprite_index+1, key->box.x+8U,  key->box.y+8U);
		move_sprite( sprite_index+3, key->box.x+16U, key->box.y+8U);

		sprite_index+=4U;

	}



	//FLUSH SPRITE MEMORY
	if(previous_sprite_index != sprite_index)
	{

		for (i=sprite_index; i!=40U; i++)
		{
			move_sprite(i,0U,200U);
			set_sprite_prop (i,0);
		}
		previous_sprite_index = sprite_index;
	}



}


void manage_animation() NONBANKED
{

	if(currentLvl == LEVEL6 || currentLvl == LEVEL13)
	{
		whiteFur.timer++;
		if(player.booleanState & WORLD_SWITCH)
		{
			if(whiteFur.timer == 5U)
			{
				whiteFur.img_index = 0U;
			}
			else if(whiteFur.timer == 10U)
			{
				whiteFur.img_index = 1U;
			}
			else if(whiteFur.timer == 15U)
			{
				whiteFur.img_index = 2U;
			}
			else if(whiteFur.timer == 20U)
			{
				whiteFur.img_index = 1U;
			}
			if(whiteFur.posX != 169U)
				whiteFur.posX++;
		}

		if(whiteFur.timer == 20U)
			whiteFur.timer = 0U;

	}
	//PLAYER ANIMATION

	if(player.state == WALK ||
		player.state == CROUCHTRANSITIONIN ||
		player.state == CROUCHTRANSITIONOUT)
	{

		player.timer++;
		if(player.booleanState & TRANSITIONNING && player.timer % 2U == 1)
		{
			player.box.x += player.dirX;
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
			player.timer = 0U;
			player.img_index = 0U;
		}



	}
	if(player.state == CROUCHWALK || player.state == CLIMBWALK)
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
	//SEAGULL ANIMATION
	SWITCH_ROM_MBC1(6);
	if(levels[currentLvl]->enemy != NULL &&
			!(levels[currentLvl]->enemy->dead && levels[currentLvl]->enemy->timer == DEAD_SEAGULL_TIME))
	{

		levels[currentLvl]->enemy->timer++;
		if(levels[currentLvl]->enemy->timer == 5U)
		{
			levels[currentLvl]->enemy->img_index = 1U;
		}
		else if(levels[currentLvl]->enemy->timer == 10U)
		{
			levels[currentLvl]->enemy->img_index = 2U;
		}
		else if(levels[currentLvl]->enemy->timer == 15U)
		{
			levels[currentLvl]->enemy->img_index = 1U;
		}
		else if(levels[currentLvl]->enemy->timer == 20U)
		{
			levels[currentLvl]->enemy->img_index = 0U;
			levels[currentLvl]->enemy->timer = 0U;
		}
		if(levels[currentLvl]->enemy->timer %2 == 1 && levels[currentLvl]->enemy->dead == 0U)
		{
			levels[currentLvl]->enemy->box.x += levels[currentLvl]->enemy->dirX;
			if(levels[currentLvl]->enemy->box.x+levels[currentLvl]->enemy->box.w > levels[currentLvl]->enemy->maxX)
			{
				levels[currentLvl]->enemy->dirX= -1;
			}
			else if(levels[currentLvl]->enemy->box.x < levels[currentLvl]->enemy->minX)
			{
				levels[currentLvl]->enemy->dirX= 1;
			}
		}
	}
	//DOGGY ANIMATION
	if(levels[currentLvl]->doggy != NULL)
	{

		levels[currentLvl]->doggy->timer++;
		if(levels[currentLvl]->doggy->timer == 5U)
		{
			levels[currentLvl]->doggy->img_index = 1U;
		}
		else if(levels[currentLvl]->doggy->timer == 10U)
		{
			levels[currentLvl]->doggy->img_index = 2U;

		}
		else if(levels[currentLvl]->doggy->timer == 15U)
		{
			levels[currentLvl]->doggy->img_index = 1U;
		}
		else if(levels[currentLvl]->doggy->timer == 20U)
		{
			levels[currentLvl]->doggy->img_index = 0U;
			levels[currentLvl]->doggy->timer = 0U;
		}
		if(levels[currentLvl]->doggy->timer % 2 == 1)
		{
			levels[currentLvl]->doggy->box.x += levels[currentLvl]->doggy->dirX;
			if(levels[currentLvl]->doggy->box.x+levels[currentLvl]->doggy->box.w > levels[currentLvl]->doggy->maxX)
			{
				levels[currentLvl]->doggy->dirX= -1;
			}
			else if(levels[currentLvl]->doggy->box.x < levels[currentLvl]->doggy->minX)
			{
				levels[currentLvl]->doggy->dirX= 1;
			}
		}
	}

}


void switch_to_level(LEVELID levelID) NONBANKED
{
	UBYTE j;

	if(levelID == NOLEVEL)
		return;
	//play_sound( SOUND_EXPLOSION );
	currentLvl = levelID;
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;
	ENABLE_RAM_MBC1;
	SWITCH_ROM_MBC1(6);

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

	currentLvl = LEVEL4;
	whiteFur.posX = 56U;
	init_screen();

	finish = 0U;
	while(!finish)
	{
		wait_vbl_done();
		keys = joypad();

		manage_input();

		if(!(player.booleanState & HASGAMEOVER)
				&& !(player.booleanState & HASVICTORY))
		{
			manage_animation();
			SWITCH_ROM_MBC1(6);
			manage_physics();
		}

		if (player.state == DEAD)
		{
			player.timer ++;
			if(player.timer == 60U)
			{
				finish = 1U;
				currentLvl = LEVEL6;
				gbt_stop();
				player.timer = 0U;
			}
		}
		set_sprites();
		SWITCH_ROM_MBC1(7);
		manage_player_sprites();
		gbt_update();

		tick_sound();

	}

}

void init_screen() NONBANKED
{
	disable_interrupts();
	finish = 0U;
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	init_sounds();
	gbt_play(song_Data, 0x02U, 0x07U);
	gbt_loop(0x01U);

	ENABLE_RAM_MBC1;

	SWITCH_ROM_MBC1(5);
	set_sprite_data(BW_INDEX, BW_SPR_LEN, tile_peanut);
	set_sprite_data(WF_INDEX, WF_SPR_LEN, tile_whitefur);
	set_sprite_data(SEA_INDEX, SEA_SPR_LEN, tile_seagull);
	set_sprite_data(ENV_INDEX, ENV_SPR_LEN, &(tile_environment[0xa<<4])); //key+lock
	set_sprite_data(STR_INDEX, STR_SPR_LEN, press_start_tiledata);
	set_sprite_data(DOG_INDEX, DOG_SPR_LEN, tile_guard);

	set_bkg_data(0, 1, tile_white);
	set_bkg_data(1U, TileEnvironmentLength, tile_environment);
	set_bkg_data(TileEnvironmentLength+1U, TileBackgroundLength, tile_background);
	set_bkg_data(TileBackgroundLength+TileEnvironmentLength+1U, TileWhalePosterLength, tile_whale_poster);

	SWITCH_ROM_MBC1(6);
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

	//init player
	player.booleanState = 0x00;
	player.box.x = 16U;
	player.box.y = 144U-GROUND_HEIGHT;
	player.box.w = PLAYER_SIZE;
	player.box.h = PLAYER_SIZE;
	player.dirX = 1;
	player.img_index = 0;
	player.state = IDLE;
	player.timer = 0;//for animation purpose and physics
	player.vely = 0;


	whiteFur.timer = 0U;
	previous_sprite_index = 0U;

	set_sprites();

}

void game_over() NONBANKED
{
	//gbt_stop();
	player.booleanState = player.booleanState | HASGAMEOVER;
	player.state = DEAD;
	player.timer = 0U;
	if(player.key != NULL)
	{
		player.key->box.x = player.key->originX;
		player.key->box.y = player.key->originY;
		player.key = NULL;
	}

	play_sound(SOUND_DEAD);
	//finish = 1U;

}

extern UBYTE credits;

void switch_to_world(WORLDID newWorldId) NONBANKED
{
	currentWorld = newWorldId;
	player.booleanState = player.booleanState | WORLD_SWITCH;

}

void victory() NONBANKED
{
	player.booleanState = player.booleanState | HASVICTORY;
	credits = 1U;
	gbt_play(victory_song_Data, 0x02U, 0x07U);
	gbt_loop(0x00U);
	player.box.y = 136U;
	SWITCH_ROM_MBC1(6);
	player.box.x = 8U;
	switch_to_level(LEVEL13);
}
void reset_game() NONBANKED
{
	SWITCH_ROM_MBC1(6);
	reset_lvl1();
	reset_lvl2();
	reset_lvl3();
	reset_lvl4();
	reset_lvl5();
	reset_lvl6();
	reset_lvl10();
	reset_lvl13();
}

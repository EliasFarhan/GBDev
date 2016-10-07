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
#include "gbt_player.h"
#include "sound.h"

#include "box_collision.h"



/*
UBYTE PeanutTileMap[] =
{
		//Peanut idle 0
	0U, 2U, 1U, 3U,
	//Peanut walk 1|4
	4U, 6U, 5U, 7U,
	8U, 10U,9U, 11U,
	12U,14U,13U,15U,
	8U, 10U,9U, 11U,
	//Peanut jump 5|20
	16U,18U,17U,19U,
	//Peanut crouch 6|24
	20U,22U,21U,23U,
	24U,26U,25U,27U,
	//28U,30U,29U,31U,
	//24U,26U,25U,27U,
	//Peanut transtition crouch in 8|32
	44U, 46U, 45U, 47U,
	48U, 50U, 49U, 51U,
	52U, 54U, 53U, 55U,
	56U, 58U, 57U, 59U,
	//Peanut transition crouch out 12|48
	56U, 58U, 57U, 59U,
	52U, 54U, 53U, 55U,
	48U, 50U, 49U, 51U,
	60U, 62U, 61U, 63U,
	//Peanut climb
	32U, 34U, 33U, 35U,
	36U, 38U, 37U, 39U,
	//Peanut Jump climb
	64U, 66U, 65U, 67U,


};
*/


extern unsigned char * song_Data[];
extern UBYTE tilemap_peanut[];


UBYTE keys;
UBYTE finish;
PLAYER player;

extern Level lvl1;
extern Level lvl2;
extern Level lvl3;
extern Level lvl4;
extern Level lvl5;
extern Level lvl6;

Level* levels[6] = {
		&lvl1,
		&lvl2,
		&lvl3,
		&lvl4,
		&lvl5,
		&lvl6
};

LEVELID currentLvl;

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
UBYTE TileWhalePosterLength = 16U;
UBYTE i;

void manage_physics(PLAYER* player);

void manage_input() NONBANKED
{
	if(!(player.booleanState & TRANSITIONNING))
	{
		if(keys & J_A)
		{
			if((!player.booleanState & HASJUMP) && player.state != JUMP && player.state != CLIMB && player.state != JUMPCLIMB && player.state != CLIMBWALK)
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
		if (keys & J_B)
		{
			if(player.key != NULL)
			{
				player.key->box.x = player.key->originX;
				player.key->box.y = player.key->originY;
				player.key = NULL;
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
}
UBYTE previous_sprite_index;
void set_sprites() NONBANKED
{

	UBYTE origin_index;
	UBYTE sprite_index;
	KEY* key;
	key = NULL;
	sprite_index = 0;
	if(player.state == IDLE)
	{
		if(player.key != NULL)
		{
			origin_index = 80U;
		}else{
		origin_index = 0U;}
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

	SWITCH_ROM_MBC1(5);
	for (i = origin_index; i != origin_index+4; i++)
	{
		set_sprite_tile( i-origin_index, tilemap_peanut[i] );
		sprite_index++;
	}
	if(levels[currentLvl]->lock != NULL && levels[currentLvl]->lock->locked)
	{
		UBYTE height;
		SWITCH_ROM_MBC1(6);
		height = 2U;
		if(levels[currentLvl]->lock->box->h >= 48U)
		{
			height = 4U;
		}

		for(i = 0; i != height; i++)
		{
			set_sprite_tile( i+sprite_index, ENV_INDEX+8U );
			if(i<height>>1)
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
			set_sprite_tile( i+sprite_index, ENV_INDEX+4U+i );
		}
		move_sprite( sprite_index+0, levels[currentLvl]->lock->box->x+4U, levels[currentLvl]->lock->box->y-(8U<<(height>>2) ));
		move_sprite( sprite_index+2, levels[currentLvl]->lock->box->x+12U, levels[currentLvl]->lock->box->y -(8U<<(height>>2)));
		move_sprite( sprite_index+1, levels[currentLvl]->lock->box->x+4U,  levels[currentLvl]->lock->box->y+8U -(8U<<(height>>2) ));
		move_sprite( sprite_index+3, levels[currentLvl]->lock->box->x+12U, levels[currentLvl]->lock->box->y+8U -(8U<<(height>>2) ));
		sprite_index+=4;
	}
	//SHOW KEYS

	if(player.key != NULL)
	{
		key = player.key;
	}
	else if(levels[currentLvl]->key != NULL && !levels[currentLvl]->key->used)
	{
		key = levels[currentLvl]->key;
	}
	if(key != NULL)
	{
		SWITCH_ROM_MBC1(6);
		for(i = 0; i != 4; i++)
		{
			set_sprite_tile( i+sprite_index, ENV_INDEX+i );

		}
		//MOVE SPRITES
		move_sprite( sprite_index+0, key->box.x+8U, key->box.y);
		move_sprite( sprite_index+2, key->box.x+16U, key->box.y);
		move_sprite( sprite_index+1, key->box.x+8U,  key->box.y+8U);
		move_sprite( sprite_index+3, key->box.x+16U, key->box.y+8U);

		sprite_index+=4;
	}
	//SHOW ENEMIES

	if(levels[currentLvl]->enemy != NULL)
	{
		SWITCH_ROM_MBC1(6);
		origin_index = levels[currentLvl]->enemy->img_index<<2;
		for(i = origin_index; i != origin_index+4U; i++)
		{
			set_sprite_tile( i-origin_index+sprite_index, SEA_INDEX+tilemap_seagull[i+origin_index] );
		}
		if(levels[currentLvl]->enemy->dirX == 1)
		{
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(sprite_index+i,0x00U);
			}
			move_sprite( sprite_index+0, levels[currentLvl]->enemy->box.x+8U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+2, levels[currentLvl]->enemy->box.x+16U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+1, levels[currentLvl]->enemy->box.x+8U,  levels[currentLvl]->enemy->box.y+8U);
			move_sprite( sprite_index+3, levels[currentLvl]->enemy->box.x+16U, levels[currentLvl]->enemy->box.y+8U);
		}
		else
		{
			for(i = 0;i!=4;i++)
			{
				set_sprite_prop(sprite_index+i,S_FLIPX);
			}
			move_sprite( sprite_index+1, levels[currentLvl]->enemy->box.x+8U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+0, levels[currentLvl]->enemy->box.x+16U, levels[currentLvl]->enemy->box.y);
			move_sprite( sprite_index+3, levels[currentLvl]->enemy->box.x+8U,  levels[currentLvl]->enemy->box.y+8U);
			move_sprite( sprite_index+2, levels[currentLvl]->enemy->box.x+16U, levels[currentLvl]->enemy->box.y+8U);
		}
		sprite_index+=4;
	}
	//FLUSH SPRITE MEMORY
	if(previous_sprite_index != sprite_index)
	{
	for (i=sprite_index; i<40; i++)
		{
			move_sprite(i,0,200);
			set_sprite_prop (i,0);
		}
		previous_sprite_index = sprite_index;
	}
	//PLAYER POSITION MANAGEMENT
	if(player.state != CLIMB && player.state != CLIMBWALK)
	{
		if(player.dirX == 1)
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
	else
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

void manage_animation() NONBANKED
{
	if(player.state == WALK || player.state == CROUCHTRANSITIONIN || player.state == CROUCHTRANSITIONOUT)
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
	else if(player.state == CROUCHWALK || player.state == CLIMBWALK)
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
	SWITCH_ROM_MBC1(6);
	if(levels[currentLvl]->enemy != NULL)
	{

		levels[currentLvl]->enemy->timer++;
		if(levels[currentLvl]->enemy->timer == 5U ||
				levels[currentLvl]->enemy->timer == 10U ||
				levels[currentLvl]->enemy->timer == 15U)
		{
			levels[currentLvl]->enemy->img_index++;
		}
		else if(levels[currentLvl]->enemy->timer == 20U)
		{
			levels[currentLvl]->enemy->img_index = 0U;
			levels[currentLvl]->enemy->timer = 0U;
		}
		if(levels[currentLvl]->enemy->timer %2 == 1)
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

}


void switch_to_level(LEVELID levelID) NONBANKED
{
	UBYTE j;

	if(levelID == NOLEVEL)
		return;
	play_sound( SOUND_EXPLOSION );
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

	currentLvl = LEVEL1;
	init_screen();

	finish = 0U;
	while(!finish)
	{
		wait_vbl_done();
		keys = joypad();
		manage_input();
		manage_animation();

		manage_physics(&player);
		set_sprites();

		gbt_update();

		tick_sound();

	}
	game_over();
}





void init_screen() NONBANKED
{
	UBYTE j;
	disable_interrupts();

	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;
	init_sounds();
	gbt_play(song_Data, 0x02U, 0x01U);
	gbt_loop(0x00U);
	ENABLE_RAM_MBC1;
	SWITCH_ROM_MBC1(5);
	set_sprite_data(BW_INDEX, BW_SPR_LEN, tile_peanut);
	set_sprite_data(WF_INDEX, WF_SPR_LEN, tile_whitefur);
	set_sprite_data(SEA_INDEX, SEA_SPR_LEN, tile_seagull);
	set_sprite_data(ENV_INDEX, ENV_SPR_LEN, &(tile_environment[0xa<<4])); //key+lock
	set_sprite_data(DOG_INDEX, DOG_SPR_LEN, tile_guard);

	set_bkg_data(0, 1, tile_white);
	set_bkg_data(1U, TileEnvironmentLength, tile_environment);
	set_bkg_data(TileEnvironmentLength+1U, TileBackgroundLength, tile_background);
	set_bkg_data(TileBackgroundLength+TileEnvironmentLength+1U, TileWhalePosterLength, tile_whale_poster);

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
	player.box.x = 16U;
	player.box.y = 144U-GROUND_HEIGHT;
	player.box.w = PLAYER_SIZE;
	player.box.h = PLAYER_SIZE;
	player.dirX = 1;
	player.img_index = 0;
	player.state = IDLE;
	player.timer = 0;//for animation purpose and physics
	player.vely = 0;
	previous_sprite_index = 0;

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

/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../game_screen.h"
#include "../box_collision.h"
#include "../sound.h"

#define BOX5LENGTH 4

size_t boxes_lvl5_length = BOX5LENGTH;

Box box_lvl5[BOX5LENGTH] =
{
		{64U,96U, 40U, 40U},
		{104U,96U, 56U, 8U},
		{72U, 128U, 8U, 32U},
		{32U, 144U, 128U, 16U}
};
LOCK locks_lvl5[1] =
{
	{&(box_lvl5[2]), 1U}
};
const unsigned char Lvl5TileMap[] =
{
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,15,17,14,12,14,12,14,12,14,12,14,12,14,12,15,17,14,12,
5,11,16,18,13,11,13,11,13,11,13,11,13,11,13,11,16,18,13,11,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,2,6,6,6,3,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,6,6,6,6,3,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,6,6,6,6,3,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,6,6,6,6,3,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,6,6,6,6,6, 6, 6, 6, 6, 6, 6,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,15,17,13,11,13,11,13,11,13,11,13,11,13,11,15,17,13,11,
5,12,16,18,14,12,14,12,14,12,14,12,14,12,14,12,16,18,14,12,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
5,12,14,12,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,11,13,11,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
};

void init_lvl5()
{

}
void manage_physics_lvl5(PLAYER* player)
{
	if(player->box.x >= 8U && player->box.x <= 16U && player->box.y > 144U-9U )
	{
		if((player->state == CLIMBWALK && player->dirY == 1) || player->state == JUMP || player->state == IDLE)
		{

			player->box.y = 9U+PLAYER_SIZE;
			if(player->state == IDLE)
			{
				player->state = JUMP;

			}
			switch_to_level(LEVEL3);
		}
	}else if(player->box.x == 160U-PLAYER_SIZE-GROUND_HEIGHT && player->box.y >= 96U &&player->box.y <= 136U && player->dirX == 1 )
	{

		player->box.x = 9U;

		switch_to_level(LEVEL6);

	}else if(player->box.x == 160U-PLAYER_SIZE-GROUND_HEIGHT && player->box.y <= 88U &&player->box.y >= 8U && player->dirX == 1 )
	{

		player->box.x = 9U;

		switch_to_level(LEVEL6);

	}else if(player->key != NULL && checkCollision(&(player->key->box), locks_lvl5[0].box))
	{
		player->key->box.x = player->key->originX;
		player->key->box.y = player->key->originY;
		player->key->used = 1U;
		player->key = NULL;
		locks_lvl5[0].box->x = 0U;
		locks_lvl5[0].box->y = 0U;
		locks_lvl5[0].box->w = 0U;
		locks_lvl5[0].box->h = 0U;
		locks_lvl5[0].locked = 0U;
		play_sound(SOUND_UNLOCK);
	}
}
void reset_lvl5()
{
	locks_lvl5[0].locked = 1U;
	//{72U, 128U, 8U, 32U},
	locks_lvl5[0].box->x = 72U;
	locks_lvl5[0].box->y = 128U;
	locks_lvl5[0].box->w = 8U;
	locks_lvl5[0].box->h = 32U;
}

Level lvl5 = {
		box_lvl5,
		boxes_lvl5_length,
		Lvl5TileMap,
		locks_lvl5
};



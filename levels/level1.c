/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */

#include <stdlib.h>
#include "../game_screen.h"
#include "../box_collision.h"

#define BOX1LENGTH 4U

size_t boxes_lvl1_length = BOX1LENGTH;

Box box_lvl1[BOX1LENGTH] =
{
	{72U, 136U, 8U, 48U},
	{48U, 136U, 24U, 48U},
	{8U, 88U, 96U, 8U },
	{72U, 72U, 8U, 56U },
};
LOCK locks_lvl1[1] =
{
	{&(box_lvl1[0]), 1U}
};
#define ENEMY1LENGTH 1U
ENEMY enemy_lvl1 [ENEMY1LENGTH] = {
		{{24U, 80U, 16U, 16U}, 1,0U, 0U, 72U, 8U}
};
UBYTE enemies_nb_lvl1 = ENEMY1LENGTH;
unsigned char Lvl1TileMap[] = {
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,12,14,12,14,12,14,3,
	5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 3,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13, 3,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 3,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13, 3,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 3,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13, 3,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 3,14,12,14,12,14,12,14,12,14,3,
   13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,15,17,3,
	5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4,12,14,12,14,16,18,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
   14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,1
};





void manage_physics_lvl1(PLAYER* player)
{

	if(player->box.x == 8U && player->box.y == 136U && (player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == -1 )
	{

		player->newX = 160U-PLAYER_SIZE;
		player->newY = 136U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL2;
		//switch_to_level(LEVEL2);

	}else if(player->box.x >= 104U && player->box.x <= 136U && player->box.y == PLAYER_SIZE+8U && player->state == CLIMBWALK)
	{

		player->box.y = 135U;
		switch_to_level(LEVEL4);
	}else if(player->box.x == 8U && player->box.y == 80U &&
			(player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == -1 )
	{

		player->newX = 160U-PLAYER_SIZE;
		player->newY = 80U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL2;
		//switch_to_level(LEVEL2);

	}else if(player->box.x == 72U-PLAYER_SIZE && player->box.y == 80U &&
			(player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == 1 )
	{

		player->newX = 72U-2U;
		player->newY = 80U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = NOLEVEL;
		//switch_to_level(LEVEL2);

	}
	else if(player->box.x == 80U && player->box.y == 80U &&
			(player->state == CROUCHWALK || player->state == CROUCH)&& player->dirX == -1 )
		{

			player->newX = 72U-PLAYER_SIZE+8U;
			player->newY = 80U;
			player->booleanState = player->booleanState | TRANSITIONNING;
			player->state = CROUCHTRANSITIONIN;
			player->timer = 0U;
			player->img_index = 0U;

			player->nextLevel = NOLEVEL;
			//switch_to_level(LEVEL2);

		}
	if(player->key != NULL && checkCollision(&(player->key->box), locks_lvl1[0].box))
		{
			player->key->box.x = player->key->originX;
			player->key->box.y = player->key->originY;
			player->key->used = 1U;
			player->key = NULL;
			locks_lvl1[0].box->x = 0U;
			locks_lvl1[0].box->y = 0U;
			locks_lvl1[0].box->w = 0U;
			locks_lvl1[0].box->h = 0U;
			locks_lvl1[0].locked = 0U;

		}

}

Level lvl1 = {
		box_lvl1,
		boxes_lvl1_length,
		Lvl1TileMap,
		locks_lvl1,
		NULL,
		enemy_lvl1,


};

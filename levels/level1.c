/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */

#include <stdlib.h>
#include "../game_screen.h"
#include "../box_collision.h"

#define BOX1LENGTH 2U

size_t boxes_lvl1_length = BOX1LENGTH;

Box box_lvl1[BOX1LENGTH] =
{

	{72U, 136U, 8U, 56U},
	{8U, 88U, 80U, 8U }
};

unsigned char Lvl1TileMap[] = {
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4,12,14,3,
	5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 6,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13, 6,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 6,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13, 6,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 6,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13, 6,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14, 6,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,15,17,3,
	5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4,12,14,12,14,16,18,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
   14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,1
};


void init_lvl1()
{

}


void manage_physics_lvl1(PLAYER* player)
{

	if(player->box.x == 8U && player->box.y == 136U && player->state == CROUCHWALK && player->dirX == -1 )
	{

		player->newX = 160U-PLAYER_SIZE;
		player->newY = 136U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL2;
		//switch_to_level(LEVEL2);

	}

}

Level lvl1 = {
		box_lvl1,
		boxes_lvl1_length,
		Lvl1TileMap,

};

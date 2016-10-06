/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../game_screen.h"

#define BOX3LENGTH 5

size_t boxes_lvl3_length = BOX3LENGTH;

const Box box_lvl3[BOX3LENGTH] =
{

		{32U,144U, 8U, 48U},
		{32U,104U, 128U, 8U},
		{56U,144U, 32U, 16U},
		{56U,144U, 96U, 8U},
		{120U,96U, 36U, 40U},
};
const unsigned char Lvl3TileMap[] =
{
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13, 2, 6, 6, 6, 3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14, 3, 3, 3, 3, 3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13, 3, 3, 3, 3, 3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14, 3, 3, 3, 3, 3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13, 3, 3, 3, 3, 3,
	5,12,14,12, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	5,11,13,11, 6,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
	5,12,14,12, 6,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
	5,11,13,11, 6,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
	5,12,14,12, 6,12,14, 2, 6, 6, 4,12,14,12,14,12,14,12,14,12,
	6,11,13,11, 6,11,13, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
};

void init_lvl3()
{

}
void manage_physics_lvl3(PLAYER* player)
{
	if(player->box.x >= 8U && player->box.x <= 16U && player->box.y > 144U-9U )
	{
		if((player->state == CLIMBWALK && player->dirY == 1) || player->state == JUMP || player->state == IDLE)
		{

			player->box.y = 8U+PLAYER_SIZE;
			if(player->state == IDLE)
				player->state = JUMP;
			switch_to_level(LEVEL2);
		}
	}else if(player->box.x >= 38U && player->box.x <= 46U && player->box.y > 144U-9U )
	{
		if((player->state == CLIMBWALK && player->dirY == 1) || player->state == JUMP || player->state == IDLE)
		{

			player->box.y = 8U+PLAYER_SIZE;
			if(player->state == IDLE)
				player->state = JUMP;
			switch_to_level(LEVEL2);
		}
	}
}

Level lvl3 = {
		box_lvl3,
		boxes_lvl3_length,
		Lvl3TileMap,
};



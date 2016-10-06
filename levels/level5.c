/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../game_screen.h"

#define BOX5LENGTH 2

size_t boxes_lvl5_length = BOX5LENGTH;

const Box box_lvl5[BOX5LENGTH] =
{
		{64U,96U, 40U, 40U},
		{104U,96U, 56U, 8U}
};
const unsigned char Lvl5TileMap[] =
{
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,2,6,6,6,3,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,6,6,6,6,3,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,6,6,6,6,3,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,6,6,6,6,3,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,6,6,6,6,6, 6, 6, 6, 6, 6, 6,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
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

	}
}

Level lvl5 = {
		box_lvl5,
		boxes_lvl5_length,
		Lvl5TileMap,

};



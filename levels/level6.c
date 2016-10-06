/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../game_screen.h"

#define BOX6LENGTH 1

size_t boxes_lvl6_length = BOX6LENGTH;

const Box box_lvl6[BOX6LENGTH] =
{
		{56U,80U, 32U, 32U}
};
const unsigned char Lvl6TileMap[] =
{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6};

void init_lvl6()
{

}
void manage_physics_lvl6(PLAYER* player)
{
	if(player->box.x == 8U && player->box.y == 136U && player->state == CROUCHWALK)
		{

			player->newX = 8U;
			player->newY = 8U+PLAYER_SIZE;

			switch_to_level(LEVEL2);

		}
}

Level lvl6 = {
		box_lvl6,
		boxes_lvl6_length,
		Lvl6TileMap,

};


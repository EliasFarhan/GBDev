/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../game_screen.h"
#include "../box_collision.h"

#define BOX6LENGTH 3

size_t boxes_lvl6_length = BOX6LENGTH;

const Box box_lvl6[BOX6LENGTH] =
{
		{104U,88U, 48U, 8U},
		{96U,136U, 40U, 8U},
		{8U,96U, 144U, 8U}
};

KEY key_lvl6[1]= {
		{{120U, 80U, 16U, 16U}, 120U, 80U, LEVEL6},
};
const unsigned char Lvl6TileMap[] =
{
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,2,6,6,6,6,6,3,
5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,6,6,6,6,6,13,14,3,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,11,13,6
};

void init_lvl6()
{

}
void manage_physics_lvl6(PLAYER* player)
{
	if(player->box.x >= 104U && player->box.x <= 136U && player->box.y > 144U-9U )
	{
		if((player->state == CLIMBWALK && player->dirY == 1) || player->state == JUMP || player->state == IDLE || player->state == WALK)
		{

			player->box.y = 8U+PLAYER_SIZE;
			if(player->state == IDLE || player->state == WALK)
			{
				player->state = JUMP;
				player->vely = 1U;
			}
			switch_to_level(LEVEL4);
		}
	}else if(player->box.x == 8U && player->box.y >= 96U &&player->box.y <= 136U && player->dirX == -1 )
	{

		player->box.x = 160U-PLAYER_SIZE-GROUND_HEIGHT-1U;

		switch_to_level(LEVEL5);

	}else if(player->box.x == 8U && player->box.y <= 88U &&player->box.y >= 8U && player->dirX == -1 )
	{

		player->box.x = 160U-PLAYER_SIZE-GROUND_HEIGHT-1U;

		switch_to_level(LEVEL5);

	}
	else if(player->key == NULL && checkCollision(&(player->box), &(key_lvl6[0].box)))
	{
		player->key = key_lvl6;
	}
}

Level lvl6 = {
		box_lvl6,
		boxes_lvl6_length,
		Lvl6TileMap,
		NULL,
		key_lvl6

};



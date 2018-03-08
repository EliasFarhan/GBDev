/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../src/game_screen.h"
#include "../src/box_collision.h"
#include "../src/physics.h"

//#define BOX4LENGTH 3

extern const size_t boxes_lvl4_length;//= BOX4LENGTH;

extern const Box box_lvl4[];/* =
{
		{8U,96U, 16U, 40U},
		{24U,104U, 112U, 8U},
		{128U, 112U, 8U,112U}
};*/
KEY key_lvl4[1]= {
		{{32U, 136U, 18U, 16U}, 32U, 136U, LEVEL4, 0U},
};
ENEMY enemy_lvl4[1]={
		{{96U, 96U, 8U, 9U}, 1,0U,0U, 128U, 28U}
};
extern const unsigned char Lvl4TileMap[];/* =
{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,11,13,6,
 5,12,15,17,14,12,14,12,14,12,14,12,14,12,14,12, 6,15,17,3,
 5,11,16,18,13,11,13,11,13,11,13,11,13,11,13,11, 6,16,18,3,
 5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12, 6,12,14,3,
 5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11, 6,11,13,3,
 5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12, 6,12,14,3,
13,11,13,11,13,11,13,35,37,43,45,11,13,11,13,11, 6,11,13,3,
 5, 5, 5,12,14,12,14,36,38,44,46,12,14,12,14,12, 6,12,14,3,
 5, 5, 5,11,13,11,13,39,41,47,49,11,13,11,13,11, 6,11,13,3,
 5, 5, 5,12,14,12,14,40,42,48,50,12,14,12,14,12, 6,12,14,3,
 5, 5, 5,11,13,11,13,11,13,11,13,11,13,11,13,11, 6,11,13,3,
 5, 5, 5,12,14,12,14,12,14,12,14,12,14,12,14,12, 6,12,14,3,
 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12, 6,12,14,3,
13,15,17,11,13,11,13,11,13,11,13,11,13,11,13,11, 6,15,17,3,
14,16,18,12,14,12,14,12,14,12,14,12,14,12,14,12,14,16,18,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
 6,6,6,6,6,6,6,6,6,6,6,6,6,12,14,12,14,12,14,6};
*/
void manage_physics_lvl4(PLAYER* player)
{
	if(player->box.x == 8U && player->box.y == 136U && (player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == -1)
	{

		player->newX = 160U;
		player->newY = 136U;

		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL3;

	}
	else if(player->box.x >= 104U && player->box.x <= 136U && player->box.y > 144U-9U )
	{
		if((player->state == CLIMBWALK && player->dirY == -1) || player->state == JUMP || player->state == IDLE || player->state == WALK)
		{

			player->box.y = 8U+PLAYER_SIZE;
			if(player->state == IDLE || player->state == WALK)
			{
				player->state = JUMP;
				player->vely = 1U;
			}
			switch_to_level(LEVEL6);
		}
	}else if(player->box.x == GROUND_HEIGHT && player->box.y == 56U &&
			(player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == -1 )
	{

		player->newX = 160U;
		player->newY = 56U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL3;

	}
	else if(player->box.x == 8U && player->box.y >= 104U &&player->box.y <= 136U && player->dirX == -1 )
	{

		player->box.x = 160U-PLAYER_SIZE-GROUND_HEIGHT-1U;

		switch_to_level(LEVEL3);

	}
	else if(player->box.x >= 136U && player->box.x <= 152U && player->box.y == PLAYER_SIZE+8U && player->state == CLIMBWALK)
	{
		if(player->state == JUMP)
			player->vely = -3;
		player->box.y = 135U;
		switch_to_level(LEVEL2);
	}
	else if(player->key == NULL && !key_lvl4[0].used &&checkCollision(&(player->box), &(key_lvl4[0].box)))
	{
		player->key = key_lvl4;
	}
	if(checkCollision(&(enemy_lvl4[0].box), &(player->box)))
	{
		manage_enemy_collision(player, (ENEMY*) enemy_lvl4);
	}
}

void reset_lvl4()
{
	enemy_lvl4[0].dead = 0U;

	key_lvl4[0].used = 0U;
	key_lvl4[0].box.x = key_lvl4[0].originX;
	key_lvl4[0].box.y = key_lvl4[0].originY;
}

Level lvl4 = {
		box_lvl4,
		boxes_lvl4_length,
		Lvl4TileMap,
		NULL,
		key_lvl4,
		enemy_lvl4

};



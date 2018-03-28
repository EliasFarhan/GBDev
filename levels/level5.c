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


extern const size_t boxes_lvl5_length;// = BOX2LENGTH;

extern const Box box_lvl5[];/* =
{
		{32U,104U, 136U, 8U},
		{32U,104U, 8U, 96U},
		{120U,104U, 32U, 24U}

};*/
SEAGULL enemy_lvl5 []= {
		{{72U, 96U, 8U, 9U}, 1,0U,0U, 120U, 44U}
};
UBYTE enemies_nb_lvl5 = 1U;
extern const unsigned char Lvl5TileMap[];/* =
{
6,12,14,12, 6,12,14,6,6,6,6,6,6,6,6,6,6,6,6,6,
5,11,13,11, 3,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,12,14,12, 3,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
5,11,13,11, 3,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,15,17,12, 3,12,14,12,14,12,14,12,14,12,14,15,17,12,14,3,
5,16,18,11, 3,11,13,11,13,11,13,11,13,11,13,16,18,11,13,3,
5,12,14,12, 3,12,14,19,21,27,29,12,14,12,14,12,14,12,14,3,
5,11,13,11, 3,11,13,20,22,28,30,11,13,11,13,11,13,11,13,3,
5,12,14,12, 3,12,14,23,25,31,33,12,14,12,14,12,14,12,14,3,
5,11,13,11, 3,11,13,24,26,32,34,11,13,11,13,11,13,11,13,11,
5,12,14,12, 3,12,14,12,14,12,14,12,14,12,14, 2, 6, 6, 6,3,
5,11,13,11, 3,11,13,11,13,11,13,11,13,11,13, 6, 6, 6, 6,3,
5,12,14,12, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,3,
5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
5,15,17,12,14,12,14,12,14,12,14,12,14,12,14,15,17,12,14,3,
5,16,18,11,13,11,13,11,13,11,13,11,13,11,13,16,18,11,13,3,
5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
};*/

void manage_physics_lvl5(PLAYER* player)
{

	if(player->box.x == 136U && player->box.y == 80U &&
			(player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == 1 )
	{

		player->newX = 0U;
		player->newY = 80U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL6;

	}
	else if(player->box.x == 136U && player->box.y == 136U &&
			(player->state == CROUCHWALK || player->state == CROUCH) && player->dirX == 1 )
	{

		player->newX = 0U;
		player->newY = 136U;
		player->booleanState = player->booleanState | TRANSITIONNING;
		player->state = CROUCHTRANSITIONIN;
		player->timer = 0U;
		player->img_index = 0U;

		player->nextLevel = LEVEL6;

	}
	else if(player->box.x >= 8U && player->box.x <= 16U && player->box.y == PLAYER_SIZE+8U && player->state == CLIMBWALK)
	{

		player->box.y = 135U;
		switch_to_level(LEVEL3);
	}
	else if(player->box.x >= 40U && player->box.x <= 48U && player->box.y == PLAYER_SIZE+8U && player->state == CLIMBWALK)
	{

		player->box.y = 135U;
		switch_to_level(LEVEL3);
	}
	if(checkCollision(&(enemy_lvl5[0].box), &(player->box)))
	{
		manage_enemy_collision(player, (SEAGULL*) enemy_lvl5);
	}
}
void reset_lvl5()
{
	enemy_lvl5[0].dead = 0U;
}

Level lvl5 = {
		box_lvl5,
		boxes_lvl5_length,
		Lvl5TileMap,
		NULL,
		NULL,
		enemy_lvl5

};



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

#include "../src/sound.h"

extern const size_t boxes_lvl5_length;// = BOX2LENGTH;

extern const Box box_lvl5[];/* =
{
		{32U,104U, 136U, 8U},
		{32U,104U, 8U, 96U},
		{120U,104U, 32U, 24U}

};*/
extern PLAYER player;
extern LOCK locks_lvl5[1];
extern const Box box_locks_lvl5_value[];
/*SEAGULL enemy_lvl5 []= {
		{{72U, 96U, 8U, 9U}, 1,0U,0U, 120U, 44U}
};*/
extern SEAGULL seagull_lvl5[];
UBYTE enemies_nb_lvl5 = 1U;
extern KEY key_lvl5[1];//= {
	//	{{120U, 80U, 18U, 16U}, 120U, 80U, LEVEL5, 0U},
//};
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

extern Box* box1;
extern Box* box2;
void manage_physics_lvl5()
{

	if(player.box.x == 136U && player.box.y == 80U &&
			(player.state == CROUCHWALK || player.state == CROUCH) && player.dirX == 1 )
	{

		player.newX = 0U;
		player.newY = 80U;
		player.booleanState = player.booleanState | TRANSITIONNING;
		player.state = CROUCHTRANSITIONIN;
		player.timer = 0U;
		player.img_index = 0U;

		player.nextLevel = LEVEL6;

	}
	if(player.box.x == 136U && player.box.y == 136U &&
			(player.state == CROUCHWALK || player.state == CROUCH) && player.dirX == 1 )
	{

		player.newX = 0U;
		player.newY = 136U;
		player.booleanState = player.booleanState | TRANSITIONNING;
		player.state = CROUCHTRANSITIONIN;
		player.timer = 0U;
		player.img_index = 0U;

		player.nextLevel = LEVEL6;
		return;

	}
	if(player.box.x >= 8U && player.box.x <= 16U && player.box.y == PLAYER_SIZE+8U && player.state == CLIMBWALK)
	{

		player.box.y = 135U;
		switch_to_level(LEVEL3);
		return;
	}
	if(player.box.x >= 40U && player.box.x <= 48U && player.box.y == PLAYER_SIZE+8U && player.state == CLIMBWALK)
	{

		player.box.y = 135U;
		switch_to_level(LEVEL3);
		return;
	}
	box1 = &(player.box);
	box2 = &(seagull_lvl5[0].box);
	if(checkCollision())
	{
		manage_seagull_collision((SEAGULL*) seagull_lvl5);
	}
	box2 = &(key_lvl5[0].box);
	if(player.key == NULL && !key_lvl5[0].used &&checkCollision())
	{
		player.key = key_lvl5;
	}
	box1 = &(player.key->box);
	box2 = locks_lvl5[0].box;
	if(player.key != NULL && checkCollision())
	{
		player.key->box.x = player.key->originX;
		player.key->box.y = player.key->originY;
		player.key->used = 1U;
		player.key = NULL;
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
	seagull_lvl5[0].dead = 0U;
	key_lvl5[0].used = 0U;
	key_lvl5[0].box.x = key_lvl5[0].originX;
	key_lvl5[0].box.y = key_lvl5[0].originY;
	locks_lvl5[0].locked = 1U;
	//{72U, 128U, 8U, 32U},
	locks_lvl5[0].box->x = box_locks_lvl5_value[0].x;//96U,128U,16U,32U
	locks_lvl5[0].box->y = box_locks_lvl5_value[0].y;
	locks_lvl5[0].box->w = box_locks_lvl5_value[0].w;
	locks_lvl5[0].box->h = box_locks_lvl5_value[0].h;
}

/*
Level lvl5 = {
		box_lvl5,
		boxes_lvl5_length,
		Lvl5TileMap,
		locks_lvl5,
		key_lvl5,
		seagull_lvl5

};
*/


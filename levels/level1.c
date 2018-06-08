/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../src/game_screen.h"
#include "../src/box_collision.h"
#include "../src/sound.h"


extern const size_t boxes_lvl1_length;// = BOX5LENGTH;
extern PLAYER player;
extern Box box_lvl1[];/* =
{
		{64U,96U, 40U, 40U},
		{104U,96U, 56U, 8U},
		{72U, 128U, 8U, 32U},
		{32U, 144U, 128U, 16U}
};*/
extern LOCK locks_lvl1[];/* =
{
	{&(box_lvl1[2]), 1U}
};*/
extern const Box box_locks_lvl1_value[];
extern const unsigned char Lvl1TileMap[];/* =
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
};*/

extern Box* box1;
extern Box* box2;

void manage_physics_lvl1()
{

	if(player.box.x >= 8U && player.box.x <= 16U && player.box.y > 144U-9U )
	{
		if((player.state == CLIMBWALK && player.dirY == 1) || player.state == JUMP || player.state == IDLE)
		{

			player.box.y = 9U+PLAYER_SIZE;
			if(player.state == IDLE)
			{
				player.state = JUMP;

			}
			switch_to_level(LEVEL3);
		}
	}
	if(player.box.x == 160U-PLAYER_SIZE-GROUND_HEIGHT && player.box.y >= 96U &&player.box.y <= 136U && player.dirX == 1 )
	{

		player.box.x = 9U;

		switch_to_level(LEVEL2);

	}
	if(player.box.x == 160U-PLAYER_SIZE-GROUND_HEIGHT && player.box.y <= 88U &&player.box.y >= 8U && player.dirX == 1 )
	{

		player.box.x = 9U;

		switch_to_level(LEVEL2);

	}

	box2 = locks_lvl1[0].box;
	box1 = &(player.key->box);

	if(player.key != NULL && checkCollision())
	{
		player.key->box.x = player.key->originX;
		player.key->box.y = player.key->originY;
		player.key->used = 1U;
		player.key = NULL;

		locks_lvl1[0].box->x = 0U;
		locks_lvl1[0].box->y = 0U;
		locks_lvl1[0].box->w = 0U;
		locks_lvl1[0].box->h = 0U;
		locks_lvl1[0].locked = 0U;
		play_sound(SOUND_UNLOCK);
	}
}
void reset_lvl1()
{
	locks_lvl1[0].locked = 1U;
	//{72U, 128U, 8U, 32U},
	locks_lvl1[0].box->x = box_locks_lvl1_value[0].x;//96U,128U,16U,32U
	locks_lvl1[0].box->y = box_locks_lvl1_value[0].y;
	locks_lvl1[0].box->w = box_locks_lvl1_value[0].w;
	locks_lvl1[0].box->h = box_locks_lvl1_value[0].h;
}

/*Level lvl1 = {
		box_lvl1,
		boxes_lvl1_length,
		Lvl1TileMap,
		locks_lvl1
};*/



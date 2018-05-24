/*
 * level1.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */


#include <stdlib.h>
#include "../src/game_screen.h"
#include "../src/physics.h"
#include "../src/box_collision.h"

extern PLAYER player;
extern const size_t boxes_lvl3_length;// = BOX3LENGTH;

extern const Box box_lvl3[];/* =
{

		{32U,144U, 8U, 48U},
		{32U,104U, 128U, 8U},
		{56U,144U, 32U, 16U},
		{56U,144U, 96U, 8U},
		{120U,96U, 36U, 40U},
		{0U,64U, 40U, 8U},
};*/
extern const unsigned char Lvl3TileMap[];/* =
{
	6,12,14,12,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,15,17,12,14,12,14,12,14,12,14,12,14,12,14,12,15,17,14,3,
	5,16,18,11,13,11,13,11,13,11,13,11,13,11,13,11,16,18,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,
	5, 6, 6, 6, 3,11,13,11,13,11,13,11,13,11,13, 2, 6, 6, 6, 3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14, 3, 3, 3, 3, 3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13, 3, 3, 3, 3, 3,
	5,12,14,12,14,12,14,12,14,12,14,12,14,12,14, 3, 3, 3, 3, 3,
	5,11,13,11,13,11,13,11,13,11,13,11,13,11,13, 3, 3, 3, 3, 3,
	5,12,14,12, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	5,11,13,11, 6,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,
	5,15,17,12, 6,12,14,12,14,12,14,12,14,12,14,12,15,17,14,12,
	5,16,18,11, 6,11,13,11,13,11,13,11,13,11,13,11,16,18,13,11,
	5,12,14,12, 6,12,14, 2, 6, 6, 4,12,14,12,14,12,14,12,14,12,
	6,11,13,11, 6,11,13, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
};*/

extern Box* box1;
extern Box* box2;
extern SEAGULL seagull_lvl3 [];
//SEAGULL seagull_lvl3 []= {
//		{{120U, 136U, 16U, 9U}, 1,0U,0U, 160U, 96U}
//};
void manage_physics_lvl3()
{
	if(player.box.x >= 8U && player.box.x <= 16U && player.box.y > 144U-9U )
	{
		if((player.state == CLIMBWALK && player.dirY == 1) || player.state == JUMP ||player.state == JUMPCLIMB || player.state == IDLE)
		{

			player.box.y = 8U+PLAYER_SIZE+1U;
			if(player.state == IDLE)
				player.state = JUMP;
			switch_to_level(LEVEL5);
		}
	}
	if(player.box.x >= 38U && player.box.x <= 46U && player.box.y > 144U-9U )
	{
		if((player.state == CLIMBWALK && player.dirY == 1) || player.state == JUMP ||player.state == JUMPCLIMB|| player.state == IDLE)
		{

			player.box.y = 8U+PLAYER_SIZE+1U;
			if(player.state == IDLE)
				player.state = JUMP;
			switch_to_level(LEVEL5);
		}
	}/*else if(player.box.x == 160U-PLAYER_SIZE-GROUND_HEIGHT && player.box.y == 56U &&
			(player.state == CROUCHWALK || player.state == CROUCH) && player.dirX == 1 )
	{

		player.newX = 0U;
		player.newY = 56U;
		player.booleanState = player.booleanState | TRANSITIONNING;
		player.state = CROUCHTRANSITIONIN;
		player.timer = 0U;
		player.img_index = 0U;

		player.nextLevel = LEVEL4;

	}*/
	if(player.box.x == 160U-PLAYER_SIZE-GROUND_HEIGHT && player.box.y >= 104U &&player.box.y <= 136U && player.dirX == 1 )
	{

		player.box.x = 9U;

		switch_to_level(LEVEL4);

	}
	if(player.box.x >= 8U && player.box.x <= 16U && player.box.y == PLAYER_SIZE+8U &&
			(player.state == CLIMBWALK||player.state == JUMP || player.state == CLIMB || player.state == JUMPCLIMB))
	{
		if(player.state == JUMP)
			player.vely = -3;
		player.box.y = 135U;
		switch_to_level(LEVEL1);
	}
	box1 = &(player.box);
	box2 = &(seagull_lvl3[0].box);
	if(checkCollision())
	{
		manage_seagull_collision((SEAGULL*) seagull_lvl3);
	}
}
void reset_lvl3()
{
	seagull_lvl3[0].dead = 0U;
}
Level lvl3 = {
		box_lvl3,
		boxes_lvl3_length,
		Lvl3TileMap,
		NULL,
		NULL,
		seagull_lvl3
};



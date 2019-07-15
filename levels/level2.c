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

extern PLAYER player;
extern const size_t boxes_lvl2_length;

extern const Box box_lvl2[];/* =
{
		{104U,88U, 48U, 8U},
		{96U,136U, 40U, 8U},
		{8U,96U, 144U, 8U},
		{0U, 136, 16U, 8U}
};*/
extern KEY key_lvl2[];
//KEY key_lvl2[1]= {
//		{{120U, 80U, 18U, 16U}, 120U, 80U, LEVEL6, 0U},
//};
extern SEAGULL seagull_lvl2 [];
/*SEAGULL seagull_lvl2 []= {
		{{56U, 136U, 8U, 9U}, 1,0U,0U, 96U, 40U}
};*/
extern const unsigned char Lvl2TileMap[];/* =
{
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,15,17,12,14,12,14,12,14,12,14,12,14,12,14,15,17,12,14,3,
13,16,18,11,13,11,13,11,13,11,13,11,13,11,13,16,18,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,51,53,59,61,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,52,54,60,62,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,55,57,63,65,12,14,12,14,12,14,12,14,3,
13,11,13,11,13,11,13,56,58,64,66,11,13,11,13,11,13,11,13,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,2,6,6,6,6,6,3,
5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,
14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,3,
13,15,17,11,13,11,11,13,13,11,13,11,13,11,13,15,17,11,13,3,
14,16,18,12,14,12,14,12,14,12,14,12,14,12,14,16,18,12,14,3,
13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,3,
6,6,14,12,14,12,14,12,14,12,14,12,6,6,6,6,6,13,14,3,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,11,13,6
};*/

extern Box* box1;
extern Box* box2;

void manage_physics_lvl2()
{
	if(player.box.x >= 104U && player.box.x <= 136U && player.box.y > 144U-9U )
	{
		if((player.state == CLIMBWALK && player.dirY == 1) || player.state == JUMP || player.state == IDLE || player.state == WALK)
		{

			player.box.y = 8U+PLAYER_SIZE;
			if(player.state == IDLE || player.state == WALK)
			{
				player.state = JUMP;
				player.vely = 1U;
			}
			switch_to_level(LEVEL4);
			return;
		}
	}
	if(player.box.x == 8U && player.box.y >= 96U &&player.box.y <= 136U && player.dirX == -1 )
	{

		player.box.x = 160U-PLAYER_SIZE-GROUND_HEIGHT-1U;

		switch_to_level(LEVEL1);
		return;
	}
	if(player.box.x == 8U && player.box.y <= 88U &&player.box.y >= 8U && player.dirX == -1 )
	{

		player.box.x = 160U-PLAYER_SIZE-GROUND_HEIGHT-1U;

		switch_to_level(LEVEL1);
		return;
	}
	box1 = &(player.box);

	box2 = &(key_lvl2[0].box);
	if(player.key == NULL && !key_lvl2[0].used && checkCollision())
	{
		player.key = key_lvl2;
	}
	box2 = &(seagull_lvl2[0].box);
	if(checkCollision())
	{
		manage_seagull_collision((SEAGULL*) seagull_lvl2);
	}
}
void reset_lvl2()
{
	seagull_lvl2[0].dead = 0U;

	key_lvl2[0].used = 0U;
	key_lvl2[0].box.x = key_lvl2[0].originX;
	key_lvl2[0].box.y = key_lvl2[0].originY;
}
/*
Level lvl2 = {
		box_lvl2,
		boxes_lvl2_length,
		Lvl2TileMap,
		NULL,
		key_lvl2,
		seagull_lvl2

};
*/

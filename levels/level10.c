/*
 * level10.c
 *
 *  Created on: May 7, 2018
 *      Author: efarhan
 */

#include <stdlib.h>
#include "../src/game_screen.h"
#include "../src/box_collision.h"
#include "../src/physics.h"

extern PLAYER player;

extern const size_t boxes_lvl10_length;

extern const Box box_lvl10[];

extern const unsigned char Lvl10TileMap[];

void manage_physics_lvl10()
{
	if(player.box.x >= 8U && player.box.x <= 16U && player.box.y > 144U-9U )
	{
		if((player.state == CLIMBWALK && player.dirY == 1) || player.state == JUMP ||player.state == JUMPCLIMB || player.state == IDLE)
		{

			player.box.y = 8U+PLAYER_SIZE+1U;
			if(player.state == IDLE)
				player.state = JUMP;
			switch_to_level(LEVEL13);
		}
	}
}

void reset_lvl10()
{
}
/*
Level lvl10 = {
		box_lvl10,
		boxes_lvl10_length,
		Lvl10TileMap,
		NULL

};
*/


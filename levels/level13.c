/*
 * level13.c
 *
 *  Created on: May 7, 2018
 *      Author: efarhan
 */




#include <stdlib.h>
#include "../src/game_screen.h"
#include "../src/box_collision.h"
#include "../src/physics.h"

extern PLAYER player;

extern const size_t boxes_lvl13_length;

extern const Box box_lvl13[];

extern const unsigned char Lvl13TileMap[];
extern LOCK locks_lvl13[];

KEY key_lvl13[1]= {
		{{120U, 136U, 18U, 16U}, 120U, 136U, LEVEL13, 0U},
};
void manage_physics_lvl13()
{
	if(player.box.x >= 8U && player.box.x <= 16U && player.box.y == PLAYER_SIZE+8U && player.state == CLIMBWALK)
	{

		player.box.y = 135U;
		switch_to_level(LEVEL10);
		return;
	}
}

void reset_lvl13()
{
}
/*
Level lvl13 = {
		box_lvl13,
		boxes_lvl13_length,
		Lvl13TileMap,
		locks_lvl13,
		&key_lvl13

};
*/

/*
 * physics.c
 *
 *  Created on: 6 Oct 2016
 *      Author: efarhan
 */
#include "game_screen.h"
#include "box_collision.h"
#include "sound.h"


extern LEVELID currentLvl;
extern Level* levels[];
extern PLAYER player;
extern Box* box1;
extern Box* box2;
Box tmp_box = {0, 0, 0, 0};
extern UBYTE i;
UBYTE groundContact = 0;
UBYTE frontContact = 0;

void manage_physics_lvl1(void);
void manage_physics_lvl2(void);
void manage_physics_lvl3(void);
void manage_physics_lvl4(void);
void manage_physics_lvl5(void);
void manage_physics_lvl6(void);
void manage_physics_lvl10(void);
void manage_physics_lvl13(void);

void manage_seagull_collision(SEAGULL* enemy)
{
	if(enemy->dead)
	{
		return;
	}
	if(player.vely >= 0 && player.box.y <= enemy->box.y-enemy->box.h+player.vely
				&& (player.box.x + player.box.w > enemy->box.x
				&& player.box.x < enemy->box.x+enemy->box.w) && enemy->box.w < 20U)
	{
		//enemy dead
		player.state = JUMP;
		player.vely = -2;
		enemy->dead = 1U;
		enemy->timer = 0U;
		play_sound(SOUND_KILL);
	}
	else
	{
		//dead
		game_over();
	}
}

void manage_key_physics(void)
{
	if(player.key != NULL)
	{
		player.key->box.x = player.box.x-1U;
		player.key->box.y = player.box.y-PLAYER_SIZE+3U;

	}
}

typedef void (*LvlHandler)(void);
static const LvlHandler lvl_handlers[15] = {
	manage_physics_lvl1, manage_physics_lvl2, manage_physics_lvl3,
	manage_physics_lvl4, manage_physics_lvl5, manage_physics_lvl6,
	0, 0, 0,
	manage_physics_lvl10, 0, 0,
	manage_physics_lvl13, 0, 0
};

void manage_level_physics(void)
{
	LvlHandler h = lvl_handlers[currentLvl];
	if(h) h();
}

void manage_static_physics2(void)
{
	UBYTE n;

	frontContact = 0U;
	groundContact = 0U;
	tmp_box.w = player.box.w;
	tmp_box.h = player.box.h;
	box1 = &tmp_box;
	if(player.box.y >= 144U-GROUND_HEIGHT)
	{
		groundContact = 1U;
	}
	n = (UBYTE)levels[currentLvl]->boxes_length;
	for(i = 0U; i != n; i++)
	{
		box2 = &(levels[currentLvl]->boxes[i]);
		//Check under player if there are ground
		if(groundContact == 0U)
		{
			tmp_box.x = player.box.x;
			tmp_box.y = player.box.y+1U;

			if(checkCollision())
			{
				groundContact = 1U;
			}
		}

		if(frontContact == 0U && (player.state == WALK || player.state == CROUCHWALK))
		{

			//Check if there is a box in front of us
			tmp_box.x = player.box.x+player.dirX;
			tmp_box.y = player.box.y;
			if(checkCollision())
			{
				frontContact = 1U;
			}

		}
		//nothing left to find once ground is known and the front check is
		//satisfied or inapplicable (front only fires while walking)
		if(groundContact && (frontContact ||
				(player.state != WALK && player.state != CROUCHWALK)))
			break;
	}
	if(groundContact == 0)
	{
		player.state = JUMP;
		player.vely = 1;
		player.timer = 0;
		player.img_index = 0;

		player.booleanState = player.booleanState | HASJUMP;

		return;
	}
	if(frontContact != 0)
	{
		//Force player to stop
		if(player.state == WALK)
		{
			player.state = IDLE;
		}
		else if(player.state == CROUCHWALK)
		{
			player.state = CROUCH;
		}
	}
	else
	{
		if(player.state == WALK || player.state == CROUCHWALK)
		{
			if((player.box.x > 8U && player.dirX == -1) || (player.box.x< 160U-8U-PLAYER_SIZE && player.dirX == 1))
			{
				//a precedence bug (`timer & 1U == 0U`) always made this move
				//unconditional; full-speed crouchwalk is kept as the shipped behavior
				player.box.x += player.dirX;
			}
		}
	}
}



void set_climbing(void)
{
	player.state = CLIMB;
	player.dirY = -1;
	player.timer = 0U;
	player.img_index = 0U;
}

void manage_climbwalk2(void)
{
	UBYTE n;

	tmp_box.w = player.box.w;
	tmp_box.h = player.box.h;
	box1 = &tmp_box;
	groundContact = 0U;
	frontContact = 0U;

	if((player.dirY == 1 && player.box.y >= 144U-GROUND_HEIGHT) ||
					(player.dirY == -1 && player.box.y <= GROUND_HEIGHT+PLAYER_SIZE))
	{
		groundContact = 1U;
	}
	if((player.box.x == 160U-GROUND_HEIGHT-PLAYER_SIZE && player.dirX == 1)
				|| (player.box.x == GROUND_HEIGHT && player.dirX == -1))
	{
		frontContact = 1U;
	}
	n = (UBYTE)levels[currentLvl]->boxes_length;
	for(i = 0U; i!=n; i++)
	{
		box2 = &(levels[currentLvl]->boxes[i]);
		if(groundContact == 0U)
		{
			tmp_box.x = player.box.x;
			tmp_box.y = player.box.y+player.dirY;

			if(checkCollision())
			{
				groundContact++;
			}
		}
		//Check if there is a box in front of us
		if(frontContact == 0U)
		{
			tmp_box.x = player.box.x+player.dirX;
			tmp_box.y = player.box.y;
			if(checkCollision())
			{
				frontContact++;
			}
		}
		//both contacts resolved: remaining boxes cannot change the result
		if(groundContact && frontContact)
			break;
	}
	if(groundContact == 0U)
	{
		player.box.y += player.dirY;
	}
	else
	{
		player.state = CLIMB;
	}
	if(frontContact == 0U)
	{

		player.box.x += player.dirX<<2;
		player.vely = 1U;
		player.state = JUMP;

	}
}



void manage_jumpclimb(void)
{
	UBYTE n;
	tmp_box.x = player.box.x+player.dirX;
	tmp_box.y = player.box.y;
	tmp_box.w = player.box.w;
	tmp_box.h = player.box.h;
	box1 = &tmp_box;
	n = (UBYTE)levels[currentLvl]->boxes_length;
	for(i = 0U; i!=n; i++)
	{
		box2 = &(levels[currentLvl]->boxes[i]);
		if(checkCollision())
		{
			set_climbing();
			return;
		}
	}
	if(player.dirX == 1)
	{
		if(player.box.x+player.box.w >= 160U-8U)
		{
			set_climbing();
		}

	}
	else if(player.dirX == -1)
	{
		if(player.box.x <= 8U)
		{
			set_climbing();
		}
	}
}

void set_idle(void)
{
	player.state = IDLE;
	player.timer = 0U;
	player.img_index = 0U;
	player.vely = 0U;
}

void manage_jumping(void)
{
	UBYTE n;
	player.timer ++;
	if(player.timer == 5U)
	{
		player.vely += 1U;
		if(player.vely > 3U)
			player.vely = 3U;

		player.timer = 0U;
	}
	player.box.y += player.vely;

	box1 = &(player.box);

	n = (UBYTE)levels[currentLvl]->boxes_length;
	for(i = 0U; i!=n; i++)
	{
		box2 = &(levels[currentLvl]->boxes[i]);
		if(checkCollision())
		{

			if(player.vely >= 0 &&
					player.box.y <= levels[currentLvl]->boxes[i].y - levels[currentLvl]->boxes[i].h + player.vely
				&& (player.box.x+player.box.w > levels[currentLvl]->boxes[i].x+2U
						&& player.box.x < levels[currentLvl]->boxes[i].x+levels[currentLvl]->boxes[i].w-2U))
			{
				player.box.y = levels[currentLvl]->boxes[i].y - levels[currentLvl]->boxes[i].h;
				set_idle();
				return;
			}
			else
			{
				if(player.box.x+PLAYER_SIZE <= levels[currentLvl]->boxes[i].x+2U)
				{
					player.box.x = levels[currentLvl]->boxes[i].x-PLAYER_SIZE;
				}
				else if( player.box.x >= levels[currentLvl]->boxes[i].x+levels[currentLvl]->boxes[i].w-2U)
				{
					player.box.x = levels[currentLvl]->boxes[i].x+levels[currentLvl]->boxes[i].w;
				}
				else
				{
					player.box.y = levels[currentLvl]->boxes[i].y+PLAYER_SIZE;
					if(player.vely < 0)
						player.vely = 1;
				}
			}
		}
	}
	if(player.box.y < 8U+PLAYER_SIZE)
	{
		player.box.y = 8U+PLAYER_SIZE;
		if(player.vely < 0)
			player.vely = 1;
	}

	if(player.box.y >= 144U-GROUND_HEIGHT)
	{
		player.box.y = 144U-GROUND_HEIGHT;
		set_idle();
		return;
	}

}
void manage_physics(void)
{
	if(player.state == JUMP || player.state == JUMPCLIMB)
	{
		manage_jumping();
		if(player.state == JUMPCLIMB)
		{
			manage_jumpclimb();
		}
	}
	else if(player.state == IDLE || player.state == WALK ||
			player.state == CROUCH || player.state == CROUCHWALK)
	{
		manage_static_physics2();
	}
	else if(player.state == CLIMBWALK)
	{
		manage_climbwalk2();
	}
	manage_level_physics();
	manage_key_physics();


}

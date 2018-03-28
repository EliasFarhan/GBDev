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


void manage_physics_lvl1(PLAYER* player);
void manage_physics_lvl2(PLAYER* player);
void manage_physics_lvl3(PLAYER* player);
void manage_physics_lvl4(PLAYER* player);
void manage_physics_lvl5(PLAYER* player);
void manage_physics_lvl6(PLAYER* player);

void manage_enemy_collision(PLAYER* player, SEAGULL* enemy)
{
	if(enemy->dead)
	{
		return;
	}
	if(player->vely >= 0U && player->box.y <= enemy->box.y-enemy->box.h+player->vely
				&& (player->box.x+player->box.w > enemy->box.x+1U
				&& player->box.x < enemy->box.x+enemy->box.w-1U) && enemy->box.w < 20U)
	{
		//enemy dead
		player->state = JUMP;
		player->vely = -2;
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

void manage_key_physics(PLAYER* player)
{
	if(player->key != NULL)
	{
		player->key->box.x = player->box.x-1U;
		player->key->box.y = player->box.y-PLAYER_SIZE+3U;

	}
}

void manage_level_physics(PLAYER* player)
{
	switch(currentLvl)
	{
	case LEVEL1:
		manage_physics_lvl1(player);
		break;
	case  LEVEL2:
		manage_physics_lvl2(player);
		break;
	case  LEVEL3:
		manage_physics_lvl3(player);
		break;
	case LEVEL4:
		manage_physics_lvl4(player);
		break;
	case  LEVEL5:
		manage_physics_lvl5(player);
		break;
	case LEVEL6:
		manage_physics_lvl6(player);
		break;
	}
}



void manage_static_physics(PLAYER* player)
{
	UBYTE contact;
	UBYTE i;
	Box tmp_box;
	tmp_box.x = player->box.x;
	tmp_box.y = player->box.y+1U;
	tmp_box.w = player->box.w;
	tmp_box.h = player->box.h;
	contact = 0;
	for(i = 0; i != levels[currentLvl]->boxes_length;i++)
	{
		if(checkCollision(&(tmp_box),  &(levels[currentLvl]->boxes[i])) ||
				player->box.y >= 144U-GROUND_HEIGHT)
		{
			contact++;
		}

	}
	if(contact == 0U)
	{
		player->state = JUMP;
		player->vely = 1;
		player->timer = 0;
		player->img_index = 0;

		player->booleanState = player->booleanState | HASJUMP;

		return;
	}
	//Check if there is a box in front of us

	tmp_box.x = player->box.x+player->dirX;
	tmp_box.y = player->box.y;
	tmp_box.w = player->box.w;
	tmp_box.h = player->box.h;
	contact = 0;
	for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
	{
		if(checkCollision(&(tmp_box),  &(levels[currentLvl]->boxes[i])))
		{
			contact++;
		}

	}
	if(contact != 0)
	{
		if(player->state == WALK)
		{
			player->state = IDLE;
		}
		else if(player->state == CROUCHWALK)
		{
			player->state = CROUCH;
		}
	}
	else
	{
		if(player->state == WALK || player->state == CROUCHWALK)
		{
			if((player->box.x>8U && player->dirX == -1) || (player->box.x< 160U-8U-PLAYER_SIZE && player->dirX == 1))
			{
				if(!(player->state == CROUCHWALK && player->timer % 2U == 1U))
				{
					player->box.x+=player->dirX;
				}
			}
		}
	}
}
void set_climbing(PLAYER* player)
{
	player->state = CLIMB;
	player->dirY = -1;
	player->timer = 0;
	player->img_index = 0;
}
void manage_climbwalk(PLAYER* player)
{
	UBYTE contact, i;
	Box tmp_box;
	tmp_box.x = player->box.x;
	tmp_box.y = player->box.y+player->dirY;
	tmp_box.w = player->box.w;
	tmp_box.h = player->box.h;
	contact = 0;
	for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
	{
		if(checkCollision(&(tmp_box),  &(levels[currentLvl]->boxes[i])) ||
				(player->dirY == 1 && player->box.y >= 144U-GROUND_HEIGHT) ||
				(player->dirY == -1 && player->box.y <= GROUND_HEIGHT+PLAYER_SIZE))
		{
			contact++;
		}

	}
	if(contact == 0U)
	{
		player->box.y += player->dirY;
	}
	else
	{
		player->state = CLIMB;
	}
	//Check if there is a box in front of us

	tmp_box.x = player->box.x+player->dirX;
	tmp_box.y = player->box.y;
	tmp_box.w = player->box.w;
	tmp_box.h = player->box.h;
	contact = 0;
	for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
	{
		if(checkCollision(&(tmp_box),  &(levels[currentLvl]->boxes[i]))
			|| (player->box.x == 160U-GROUND_HEIGHT-PLAYER_SIZE && player->dirX == 1)
			|| (player->box.x == GROUND_HEIGHT && player->dirX == -1))
		{
			contact++;
		}

	}
	if(contact == 0U)
	{

		player->box.x += player->dirX<<1;
		player->vely = 1U;
		player->state = JUMP;

	}
}
void manage_jumpclimb(PLAYER* player)
{
	UBYTE i;
	Box tmp_box;
	tmp_box.x = player->box.x+player->dirX;
	tmp_box.y = player->box.y;
	tmp_box.w = player->box.w;
	tmp_box.h = player->box.h;

	for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
	{
		if(checkCollision(&(tmp_box), &(levels[currentLvl]->boxes[i])))
		{
			set_climbing(player);
		}
	}
	if(player->dirX == 1)
	{
		if(player->box.x+player->box.w >= 160U-8U)
		{
			set_climbing(player);
		}

	}
	else if(player->dirX == -1)
	{
		if(player->box.x <= 8U)
		{
			set_climbing(player);
		}
	}
}
void set_idle(PLAYER* player)
{
	player->state = IDLE;
	player->timer = 0U;
	player->img_index = 0U;
	player->vely = 0U;
}
void manage_jumping(PLAYER* player)
{
	UBYTE i;
	player->timer ++;
	if(player->timer == 5U)
	{
		player->vely += 1U;
		if(player->vely > 3U)
			player->vely = 3U;

		player->timer = 0U;
	}
	player->box.y += player->vely;



	for(i = 0; i!=levels[currentLvl]->boxes_length;i++)
	{
		if(checkCollision(&(player->box), &(levels[currentLvl]->boxes[i])))
		{

			if(player->vely >= 0U &&
					player->box.y <=
					levels[currentLvl]->boxes[i].y - levels[currentLvl]->boxes[i].h + player->vely
				&& (player->box.x+player->box.w > levels[currentLvl]->boxes[i].x+2U
						&& player->box.x < levels[currentLvl]->boxes[i].x+levels[currentLvl]->boxes[i].w-2U))
			{
				player->box.y = levels[currentLvl]->boxes[i].y - levels[currentLvl]->boxes[i].h;
				set_idle(player);
				return;
			}
			else
			{
				if(player->box.x+PLAYER_SIZE <= levels[currentLvl]->boxes[i].x+2U)
				{
					player->box.x = levels[currentLvl]->boxes[i].x-PLAYER_SIZE;
				}
				else if( player->box.x >= levels[currentLvl]->boxes[i].x+levels[currentLvl]->boxes[i].w-2U)
				{
					player->box.x = levels[currentLvl]->boxes[i].x+levels[currentLvl]->boxes[i].w;
				}
				else
				{
					player->box.y = levels[currentLvl]->boxes[i].y+PLAYER_SIZE;
					if(player->vely < 0U)
						player->vely = 1;
				}
			}
		}
	}
	if(player->box.y < 8U+PLAYER_SIZE)
	{
		player->box.y = 8U+PLAYER_SIZE;
		if(player->vely < 0U)
			player->vely = 1;
	}

	if(player->box.y >= 144U-GROUND_HEIGHT)
	{
		player->box.y = 144U-GROUND_HEIGHT;
		set_idle(player);
		return;
	}

}
void manage_physics(PLAYER* player)
{
	if(player->state == JUMP || player->state == JUMPCLIMB)
	{
		manage_jumping(player);
		if(player->state == JUMPCLIMB)
		{
			manage_jumpclimb(player);
		}
	}
	else if(player->state == IDLE || player->state == WALK ||
			player->state == CROUCH || player->state == CROUCHWALK)
	{
		manage_static_physics(player);
	}
	else if(player->state == CLIMBWALK)
	{
		manage_climbwalk(player);
	}

	manage_level_physics(player);
	manage_key_physics(player);


}



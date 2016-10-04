/*
 * box_collision.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */
#include "box_collision.h"

char checkCollision(Box* a, Box* b) NONBANKED
{
	return !(b->x >= a->x+a->w ||
			b->x+b->w <= a->x ||
			b->y <= a->y-a->h ||
			b->y-b->h >= a->y);
}



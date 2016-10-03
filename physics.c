/*
 * physics.c
 *
 *  Created on: 3 Oct 2016
 *      Author: efarhan
 */
#include "physics.h"
#include <stdlib.h>

char checkCollision(Box* a, Box* b)
{
	return !(b->x > a->x+a->w ||
			b->x+b->w < a->x ||
			b->y < a->y-a->h ||
			b->y-b->h > a->y);
}





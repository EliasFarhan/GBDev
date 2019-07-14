/*
 * box_collision.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */
#include "box_collision.h"


Box* box1;
Box* box2;
UBYTE checkCollision() NONBANKED
{
	if(box2->x >= box1->x+box1->w) return 0;
	if (box2->x+box2->w <= box1->x) return 0;
	if (box2->y <= box1->y-box1->h) return 0;
	if (box2->y-box2->h >= box1->y) return 0;
	return 1;
}

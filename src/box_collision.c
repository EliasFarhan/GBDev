/*
 * box_collision.c
 *
 *  Created on: 4 Oct 2016
 *      Author: efarhan
 */
#include "box_collision.h"
/*
int abs(int x) NONBANKED
{
	if(x > 0)
	{
		return -x;
	}
	return x;
}
*/

Box* box1;
Box* box2;
char checkCollision() NONBANKED
{
	if (box2->x >= box1->x+box1->w) return 0;
	if (box2->x+box2->w <= box1->x) return 0;
	if (box2->y <= box1->y-box1->h) return 0;
	if (box2->y-box2->h >= box1->y) return 0;
	return 1;
			/*if ((abs((a->x+(a->w >> 1)) - (b->x+(b->w >> 1))) - ((a->w >> 1) + (b->w >> 1))) >= 0) return 0;
	if ((abs((a->y-(a->h >> 1)) - (b->y-(b->h >> 1))) - ((a->h >> 1) + (b->h >> 1))) >= 0) return 0;
	return 1;*/

}



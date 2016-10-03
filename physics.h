/*
 * physics.h
 *
 *  Created on: 3 Oct 2016
 *      Author: efarhan
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_
#include <gb/gb.h>

typedef struct
{
	UBYTE x;
	UBYTE y;
	UBYTE w;
	UBYTE h;
} Box;

char checkCollision(Box* a, Box* b);

#endif /* PHYSICS_H_ */

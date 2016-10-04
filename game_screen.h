#ifndef GAME_SCREEN_H_
#define GAME_SCREEN_H_

#include <gb/gb.h>
#include <stdlib.h>

#define HASJUMP 0x01
#define TRANSITIONNING 0x04
typedef enum {
	LEVEL1 = 0U,
	LEVEL2 = 1U
} LEVELID;
typedef struct
{
	UBYTE x;
	UBYTE y;
	UBYTE w;
	UBYTE h;
} Box;
enum AnimationState
{
	IDLE,
	WALK,
	JUMP,
	CROUCH,
	CROUCHWALK,
	CROUCHTRANSITIONIN,
	CROUCHTRANSITIONOUT,
	CLIMB,
	CLIMBWALK,
	JUMPCLIMB
};
typedef struct{
	Box box;
	enum AnimationState state;//0 right, 1 left, 2 up, 3 down
	UBYTE img_index; //for animations with more than one frame
	BYTE dir; //for walk and jump
	UBYTE timer; //for animations
	UBYTE booleanState;//JUMP TRANSITIONNING
	BYTE vely;//y-velocity for jump
	LEVELID nextLevel;
	UBYTE newX;
	UBYTE newY;

} PLAYER;
typedef struct
{
	Box* boxes;
	size_t boxes_length;
	unsigned char* LvlTileMap;


} Level;





void init_screen();
void game_screen();
void game_over();
void switch_to_level(LEVELID);

#endif

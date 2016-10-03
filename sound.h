#ifndef __GB_GAME_SOUND__
#define __GB_GAME_SOUND__

#define ENABLE_SOUND 1

#include <types.h>
// Being explicit since these are used as indices and this is probably some old ass compiler with quirks
typedef enum
{
	SOUND_SHOOTING = 0,
	SOUND_ENEMY_SHOOTING = 1,
	SOUND_EXPLOSION = 2,
	SOUND_LOSE = 3,
	SOUND_END = 4
} SoundID;

typedef struct
{
	UINT8 nr10;
	UINT8 nr11;
	UINT8 nr12;
	UINT8 nr13;
	UINT8 nr14;
} DataChannel1;


typedef struct
{
	UINT8 nr21;
	UINT8 nr22;
	UINT8 nr23;
	UINT8 nr24;
} DataChannel2;


typedef struct
{
	UINT8 nr30;
	UINT8 nr31;
	UINT8 nr32;
	UINT8 nr33;
	UINT8 nr34;
} DataChannel3;


typedef struct
{
	UINT8 nr41;
	UINT8 nr42;
	UINT8 nr43;
	UINT8 nr44;
} DataChannel4;


typedef enum
{
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4
} Channel;

typedef struct
{
	UINT8 playTime;     // playTime in frames before another sound can play
	UINT8 soundLevelLeft;   // level (between 0-7)
	UINT8 soundLevelRight;   // level (between 0-7)
	Channel channel;
	union
	{
		DataChannel1 chan1;
		DataChannel2 chan2;
		DataChannel3 chan3;
		DataChannel4 chan4;
	} data;

	UINT8 speed_haxor1;
	UINT8 speed_haxor2;
	UINT8 speed_haxor3;
	UINT8 speed_haxor4;
	UINT8 speed_haxor5;
	UINT8 speed_haxor6;
	UINT8 speed_haxor7;

} SoundData;


void init_sounds();
void tick_sound();
void play_sound( SoundID sound );

#endif


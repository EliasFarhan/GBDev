#include "sound.h"
#include <gb/gb.h>

SoundData gSounds[SOUND_END];
UINT8 gC1Playtime, gC2Playtime, gC3Playtime, gC4Playtime;

// In progress
void init_sounds()
{
	gC1Playtime = 1, gC2Playtime = 1, gC3Playtime = 1, gC4Playtime = 1;

	// Explosion
	
	gSounds[SOUND_JUMP].playTime		= 7;
	gSounds[SOUND_JUMP].soundLevelLeft	= 7;
	gSounds[SOUND_JUMP].soundLevelRight	= 7;
	gSounds[SOUND_JUMP].channel			= CHANNEL_1;

	gSounds[SOUND_JUMP].data.chan1.nr10 = 0x3B;
	gSounds[SOUND_JUMP].data.chan1.nr11 = 0xF0;
	gSounds[SOUND_JUMP].data.chan1.nr12 = 0xF1;
	gSounds[SOUND_JUMP].data.chan1.nr13 = 0x87;
	gSounds[SOUND_JUMP].data.chan1.nr14 = 0x87;

	// Pew pew laser sounds
	gSounds[SOUND_UNLOCK].playTime			= 5;
	gSounds[SOUND_UNLOCK].soundLevelLeft	= 7;
	gSounds[SOUND_UNLOCK].soundLevelRight	= 7;
	gSounds[SOUND_UNLOCK].channel			= CHANNEL_1;

	gSounds[SOUND_UNLOCK].data.chan1.nr10 = 0xCE;
	gSounds[SOUND_UNLOCK].data.chan1.nr11 = 0x82;
	gSounds[SOUND_UNLOCK].data.chan1.nr12 = 0xF0;
	gSounds[SOUND_UNLOCK].data.chan1.nr13 = 0xC1;
	gSounds[SOUND_UNLOCK].data.chan1.nr14 = 0x87;

	// Ship death
	gSounds[SOUND_KILL].playTime			= 5;
	gSounds[SOUND_KILL].soundLevelLeft		= 7;
	gSounds[SOUND_KILL].soundLevelRight	= 7;
	gSounds[SOUND_KILL].channel			= CHANNEL_4;

	gSounds[SOUND_KILL].data.chan4.nr42 = 0xF3;
	gSounds[SOUND_KILL].data.chan4.nr43 = 0x89;

	gSounds[SOUND_KILL].data.chan4.nr44 = 0x80;

	// Fail, player ship explosion
	gSounds[SOUND_DEAD].playTime		= 5;
	gSounds[SOUND_DEAD].soundLevelLeft	= 7;
	gSounds[SOUND_DEAD].soundLevelRight	= 7;
	gSounds[SOUND_DEAD].channel			= CHANNEL_4;

	gSounds[SOUND_DEAD].data.chan4.nr42 = 0xF7;
	gSounds[SOUND_DEAD].data.chan4.nr43 = 0x99;
	gSounds[SOUND_DEAD].data.chan4.nr44 = 0x80; //can't tweak this anymore
}

void tick_sound()
{
	if( gC1Playtime > 0 )
	{
		gC1Playtime = gC1Playtime - 1;
		if( gC1Playtime == 0 )
		{
			 NR52_REG &= 0x8E;
		}
	}

	if( gC2Playtime > 0 )
	{
		gC2Playtime = gC2Playtime - 1;
		if( gC2Playtime == 0 )
		{
			NR52_REG &= 0x8D;
		}
	}

	if( gC3Playtime > 0 )
	{
		gC3Playtime = gC3Playtime - 1;
		if( gC3Playtime == 0 )
		{
			NR52_REG &= 0xFB; //turn off bit 2 to disable channel 3 sound completely
		}
	}

	if( gC4Playtime > 0 )
	{
		gC4Playtime = gC4Playtime - 1;
		if( gC4Playtime == 0 )
		{
			NR52_REG = 0x87;
		}
	}
}

void play_sound( SoundID sound )
{
	if( !ENABLE_SOUND )
		return;

	switch( gSounds[sound].channel )
	{
	case CHANNEL_1:
		if( gC1Playtime > 0 ) 
			return;

		gC1Playtime = gSounds[sound].playTime;
		NR10_REG = gSounds[sound].data.chan1.nr10;
		NR11_REG = gSounds[sound].data.chan1.nr11;
		NR12_REG = gSounds[sound].data.chan1.nr12;
		NR13_REG = gSounds[sound].data.chan1.nr13;
		NR14_REG = gSounds[sound].data.chan1.nr14;

		NR50_REG = gSounds[sound].soundLevelRight;
		NR50_REG |= gSounds[sound].soundLevelLeft << 4;
		NR51_REG |= 0x11;
		NR52_REG |= 0x1; //enable channel 1 sound
		break;
	case CHANNEL_2:
		if( gC2Playtime > 0 ) 
			return;

		gC2Playtime = gSounds[sound].playTime;
		NR21_REG = gSounds[sound].data.chan2.nr21;
		NR22_REG = gSounds[sound].data.chan2.nr22;
		NR23_REG = gSounds[sound].data.chan2.nr23;
		NR24_REG = gSounds[sound].data.chan2.nr24;

		NR50_REG = gSounds[sound].soundLevelRight;
		NR50_REG |= gSounds[sound].soundLevelLeft << 4;
		NR51_REG |= 0x22;
		NR52_REG |= 0x2; //enable channel 2 sound
		break;
	case CHANNEL_3:
		if( gC3Playtime > 0 ) 
			return;

		gC3Playtime = gSounds[sound].playTime;
		NR30_REG = gSounds[sound].data.chan3.nr30;
		NR31_REG = gSounds[sound].data.chan3.nr31;
		NR32_REG = gSounds[sound].data.chan3.nr32;
		NR33_REG = gSounds[sound].data.chan3.nr33;
		NR34_REG = gSounds[sound].data.chan3.nr34;

		NR50_REG = gSounds[sound].soundLevelRight;
		NR50_REG |= gSounds[sound].soundLevelLeft << 4;
		NR51_REG |= 0x44;
		NR52_REG |= 0x4; //enable channel 3 sound
		break;
	case CHANNEL_4:
		if( gC4Playtime > 0 ) 
			return;

		gC4Playtime = gSounds[sound].playTime;
		NR41_REG = gSounds[sound].data.chan4.nr41;
		NR42_REG = gSounds[sound].data.chan4.nr42;
		NR43_REG = gSounds[sound].data.chan4.nr43;
		NR44_REG = gSounds[sound].data.chan4.nr44;

		NR50_REG = gSounds[sound].soundLevelRight;
		NR50_REG |= gSounds[sound].soundLevelLeft << 4;
		NR51_REG |= 0x88;
		NR52_REG |= 0x8; //enable channel 4 sound
		break;
	default:
		//do we have any sort of assertions? print statements?
		break;
	};
}


/*
 * game_screen.c
 *
 *  Created on: 28 juil. 2014
 *      Author: efarhan
 */

#include <gb/gb.h>
#include "game_screen.h"

#define ALPHABET_LEN 58u
#define WUTHRER_SIZE 119u
#define TONI_SIZE 116u
#define BOX_CLOSE_SIZE 139u
#define CARO_SIZE 119u

#define LOWER_A 32


enum ScreenType
{
	WUTHRER = 0u,
	TONI = 1u,
	CARO = 2u,
	CLOSE_BOX = 3u,
	OPEN_BOX = 4u,
	CLOSE_BOX_CHOICE = 5u
};

UBYTE finish;
UBYTE keys;

UBYTE screenType;

BYTE* currentTxt;
extern UBYTE credits;

//text variable
extern const BYTE intro1[];
extern const BYTE choice1[];

extern const BYTE answer1[];
extern const BYTE answer2[];
extern const BYTE answer3[];

extern const BYTE choice2[];
extern const BYTE answer2_2[];
extern const BYTE answer2_3[];

extern const BYTE box1[];
extern const BYTE box2[];
extern const BYTE box3[];
extern const BYTE box4[];

extern const BYTE tony1[];
extern const BYTE tony2[];

extern const BYTE wuthrer1[];
extern const BYTE wuthrer2[];
extern const BYTE wuthrer3[];

extern const BYTE caro1[];
extern const BYTE caro2[];

extern const BYTE choice3[];

extern const BYTE answer3_1_w_1[];
extern const BYTE answer3_1_w_2[];
extern const BYTE answer3_1_t_3[];
extern const BYTE answer3_1_w_4[];
extern const BYTE answer3_1_c_5[];
extern const BYTE answer3_1_c_6[];
extern const BYTE answer3_1_t_7[];
extern const BYTE answer3_1_t_8[];
extern const BYTE answer4_1_t_9[];

extern const BYTE answer3_2_w_1[];
extern const BYTE answer3_2_t_2[];
extern const BYTE answer3_2_w_3[];
extern const BYTE answer3_2_t_4[];
extern const BYTE answer3_2_t_5[];
extern const BYTE answer3_2_w_6[];
extern const BYTE answer3_2_w_7[];
extern const BYTE answer3_2_w_8[];
extern const BYTE answer3_2_w_9[];
extern const BYTE answer3_2_c_10[];
extern const BYTE answer3_2_c_11[];

extern const BYTE answer3_3_c_1[];
extern const BYTE answer3_3_w_2[];
extern const BYTE answer3_3_w_3[];
extern const BYTE answer3_3_t_4[];
extern const BYTE answer3_3_t_5[];
extern const BYTE answer3_3_t_6[];
extern const BYTE answer3_3_t_7[];
extern const BYTE answer3_3_t_8[];
extern const BYTE answer3_3_t_9[];

extern const BYTE choice4[];

//title screen image
extern unsigned char wuthrer_gb_wbox_tiledata[];
extern unsigned char wuthrer_gb_wbox_tilemap[];
extern unsigned char box_close_gb_wbox_tiledata[];
extern unsigned char box_close_gb_wbox_tilemap[];
extern unsigned char toni_gb_wbox_tiledata[];
extern unsigned char toni_gb_wbox_tilemap[];
extern unsigned char caro_gb_wbox_tiledata[];
extern unsigned char caro_gb_wbox_tilemap[];

extern unsigned char Alphabet[];

extern BYTE wuthrer_test[];





void victory() NONBANKED
{
}
unsigned char tile;
void init_text_bg() NONBANKED
{
	const UBYTE origin_x = 1u, origin_y = 14u;
	UBYTE i, j, index, offset;
	BYTE letter, upperAlpha, lowerAlpha;

	for(i = 0; i != 3; i++)
	{
		offset = i + i;
		offset = offset + (offset << 3u);
		for(j = 0; j != 18; j++)
		{
			
			tile = 0u;
			index = offset+j;
			letter = currentTxt[index];
			if(letter == '\0')
			{
				i = 2;
				break;
			}

			upperAlpha = letter - 'A';
			if(upperAlpha >= 0 || upperAlpha < 26)
			{
				tile = upperAlpha;
			}
			

			lowerAlpha = letter - 'a';
			if(lowerAlpha >= 0 || lowerAlpha < 26)
			{
				tile =  LOWER_A+lowerAlpha;
			}

			if(letter == ' ')
			{
				continue;
			}

			if(letter == ',')
			{
				tile = 29u;
			}
			if(letter == '.')
			{
				tile = 28u;
			}
			if(letter == '!')
			{
				tile = 27u;
			}
			if(letter == '?')
			{
				tile = 26u;
			}
			if(letter == '\'')
			{
				tile = 30u;
			}
			if(letter == ':')
			{
				tile = 31u;
			}

			if(screenType == WUTHRER)
			{
				tile += WUTHRER_SIZE;
			}
			else if(screenType == CLOSE_BOX)
			{
				tile += BOX_CLOSE_SIZE;
			}
			else if(screenType == TONI)
			{
				tile += TONI_SIZE;
			}
			else if(screenType == CARO)
			{
				tile += CARO_SIZE;
			}
			set_bkg_tiles(origin_x+j, origin_y+i, 1, 1, &tile);
		}
	}
}


void init_screen() NONBANKED
{
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	//init_sounds();
	//gbt_play(song_Data, 0x02U, 0x07U);
	//gbt_loop(0x01U);


	//TODO sprite alphabet

	//set current dialog bg
	if(screenType == WUTHRER)
	{
		
		SWITCH_ROM_MBC1(1);
		set_bkg_data(0, WUTHRER_SIZE, wuthrer_gb_wbox_tiledata);
		
		SWITCH_ROM_MBC1(2);
		set_win_data(WUTHRER_SIZE, ALPHABET_LEN, Alphabet);
	}
	else if(screenType == CLOSE_BOX)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_data(0, BOX_CLOSE_SIZE, box_close_gb_wbox_tiledata);
		
		SWITCH_ROM_MBC1(2);
		set_win_data(BOX_CLOSE_SIZE, ALPHABET_LEN, Alphabet);
	}
	else if(screenType == TONI)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_data(0, TONI_SIZE, toni_gb_wbox_tiledata);
		
		SWITCH_ROM_MBC1(2);
		set_win_data(TONI_SIZE, ALPHABET_LEN, Alphabet);
	}
	else if(screenType == CARO)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_data(0, CARO_SIZE, caro_gb_wbox_tiledata);
		
		SWITCH_ROM_MBC1(2);
		set_win_data(CARO_SIZE, ALPHABET_LEN, Alphabet);
	}
	//set_bkg_data(1U, TileEnvironmentLength, tile_environment);
	//set_bkg_data(TileEnvironmentLength+1U, TileBackgroundLength, tile_background);
	//set_bkg_data(TileBackgroundLength+TileEnvironmentLength+1U, TileWhalePosterLength, tile_whale_poster);
	//Background

	if(screenType == WUTHRER)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_tiles(0,0, 20, 18, wuthrer_gb_wbox_tilemap);
		
		SWITCH_ROM_MBC1(2);
		init_text_bg();
	}
	else if (screenType == CLOSE_BOX)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_tiles(0,0, 20, 18, box_close_gb_wbox_tilemap);
		
		SWITCH_ROM_MBC1(2);
		init_text_bg();
	
	}
	else if (screenType == TONI)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_tiles(0,0, 20, 18, toni_gb_wbox_tilemap);
		
		SWITCH_ROM_MBC1(2);
		init_text_bg();
	
	}
	else if(screenType == CARO)
	{
		SWITCH_ROM_MBC1(1);
		set_bkg_tiles(0,0, 20, 18, caro_gb_wbox_tilemap);
		
		SWITCH_ROM_MBC1(2);
		init_text_bg();
	}
	SPRITES_8x8;//TODO: why not 8x16?

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
}

void game_over() NONBANKED
{
	//gbt_stop();
	
	//finish = 1U;

}
void manage_input() NONBANKED
{

	if(keys & J_A)
	{
		if(currentTxt == intro1)
		{
			currentTxt = wuthrer1;
			screenType = WUTHRER;
			init_screen();
		}
		else if(currentTxt == wuthrer1)
		{
			currentTxt = tony1;
			screenType = TONI;
			init_screen();
		}
		else if(currentTxt == tony1)
		{
			currentTxt = caro1;
			screenType = CARO;
			init_screen();
		}
	}
}
void game_screen() NONBANKED
{
	screenType = CLOSE_BOX;
	SWITCH_ROM_MBC1(2);
	currentTxt = intro1;
	init_screen();
	finish = 0U;
	while(!finish)
	{
		wait_vbl_done();
		keys = joypad();

		manage_input();
		//manage_text_sprites();
		//gbt_update();

		//tick_sound();

	}

}

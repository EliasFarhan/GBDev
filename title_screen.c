#include <gb/gb.h>

//title screen image
extern unsigned char title_screen_tiledata[];
extern unsigned char title_screen_tilemap[];
extern unsigned char press_start_tiledata[];
extern unsigned char press_start_tilemap[];


#define PS_ORIGIN_X 0x30U
#define PS_TEXT_POSY 0x8aU

void title_graphics(UBYTE pstart) BANKED {
	UBYTE i;



	//Show PRESS START
	i = 0U;
	while(i != 0x0aU)
	{
		set_sprite_tile( i, press_start_tilemap[i] );
		if (pstart == 0) {
			move_sprite(i,0U,200U);
		}
		else
		{
			if(i >= 5U)
			{
				move_sprite( i, PS_ORIGIN_X+(i<<0x3U)+0x8U, PS_TEXT_POSY );
			}
			else
			{
				move_sprite( i, PS_ORIGIN_X+(i<<0x3U), PS_TEXT_POSY );
			}
		}
		i++;

	}

}


void title_screen() BANKED {

	UBYTE keys, i,j;
	UBYTE counter = 0;
	UBYTE pstart = 1;
	ENABLE_RAM_MBC1;
	wait_vbl_done();
	disable_interrupts();
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	DISPLAY_OFF;

	SWITCH_ROM_MBC1(3);
	set_bkg_data(0x00, 0x68, title_screen_tiledata);
	for(i = 0; i != 20; i++)
		{
			for(j = 0; j!= 18; j++)
			{
				set_bkg_tiles(i,j,1,1, &title_screen_tilemap[i*18+j]);
			}
		}

	SWITCH_ROM_MBC1(5);
	set_sprite_data( 0U, 0x6U, press_start_tiledata);
	SHOW_BKG;
	SHOW_WIN;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (keys & (J_A|J_START)) {
			break;
		}
		title_graphics(pstart);
		counter++;
		if(counter == 5)
		{
			if(pstart == 0)
				pstart = 1U;
			else
				pstart = 0U;
			counter = 0;
		}
	}
}

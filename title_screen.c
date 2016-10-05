#include <gb/gb.h>
#include <gb/drawing.h>

//title screen image
extern unsigned char title_screen_tiledata[];
extern unsigned char press_start_tiledata[];
extern unsigned char press_start_tilemap[];


#define ORIGIN_X 0x30U
#define TEXT_POSY 0x8aU

void title_graphics(UBYTE pstart) NONBANKED {
	UBYTE i;
	draw_image(title_screen_tiledata);
	//Show PRESS START
	for(i = 0U; i != 10U;i++)
		{
			set_sprite_tile( i, press_start_tilemap[i] );
		}

	if (!pstart) {
		for(i = 0U; i != 10U;i++)
		{
			move_sprite(i,0U,200U);
		}
	}
	else
	{
		for(i = 0U; i != 10U;i++)
		{
			if(i >= 5U)
			{
				move_sprite( i, ORIGIN_X+(i<<0x3U)+0x8U, TEXT_POSY );
			}
			else
			{
				move_sprite( i, ORIGIN_X+(i<<0x3U), TEXT_POSY );
			}
		}


	}
}

void title_screen() NONBANKED {
	UBYTE counter = 0, pstart = 1, keys = 0;

	DISPLAY_OFF;
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	ENABLE_RAM_MBC1;
	SWITCH_ROM_MBC1(3);
	set_sprite_data( 0U, 0x6U, press_start_tiledata);

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
			pstart = !pstart;
			counter = 0;
		}
	}
}

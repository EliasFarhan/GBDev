#include <gb/gb.h>
#include <gb/drawing.h>

extern unsigned char staffroll_tiledata[];
extern unsigned char staffroll_tilemap[];



void credits_screen() NONBANKED {
	UBYTE pstart = 0;
	UBYTE keys = 0;
	wait_vbl_done();
	disable_interrupts();
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	DISPLAY_OFF;

	ENABLE_RAM_MBC1;
	SWITCH_ROM_MBC1(8);
	set_bkg_data(0U,124U,staffroll_tiledata);
	set_bkg_tiles(0,0,20,18, staffroll_tilemap);
	SPRITES_8x8;//TODO: why not 8x16?
	DISPLAY_ON;
	SHOW_BKG;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (keys & (J_A|J_START))
		{
			break;
		}
		pstart++;
	}
}

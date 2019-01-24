#include <gb/gb.h>
#include <gb/drawing.h>

extern unsigned char kwakwa_logo_tiledata[];

extern unsigned char kwakwa_logo_tilemap[];
//void kwakwa_graphics() NONBANKED {
	//SWITCH_ROM_MBC1(3);
	//draw_image(kwakwa_logo_tiledata);
//}

void kwakwa_screen() NONBANKED {
	UBYTE pstart = 0;
	UBYTE keys = 0;
	wait_vbl_done();
	disable_interrupts();
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	DISPLAY_OFF;
	ENABLE_RAM_MBC1;

	SWITCH_ROM_MBC1(3);
	set_bkg_data(0,255,kwakwa_logo_tiledata);

	set_bkg_tiles(0,0,20,18,kwakwa_logo_tilemap);
	DISPLAY_ON;
	SHOW_BKG;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (pstart == 30) {
			break;
		}
		//kwakwa_graphics();
		pstart++;
	}
}

#include <gb/gb.h>
#include <gb/drawing.h>

extern unsigned char kwakwa_logo_tiledata[];

void kwakwa_graphics() NONBANKED {
	SWITCH_ROM_MBC1(3);
	draw_image(kwakwa_logo_tiledata);
}

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

	DISPLAY_ON;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (pstart == 20) {
			break;
		}
		kwakwa_graphics();
		pstart++;
	}
}

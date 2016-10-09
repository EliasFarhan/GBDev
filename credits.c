#include <gb/gb.h>
#include <gb/drawing.h>

extern unsigned char staffroll_tiledata[];

void credits_graphics() NONBANKED {
	SWITCH_ROM_MBC1(8);
	draw_image(staffroll_tiledata);
}

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

	DISPLAY_ON;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (pstart == 20) {
			break;
		}
		credits_graphics();
		pstart++;
	}
}

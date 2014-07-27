#include <gb/gb.h>
#include <gb/drawing.h>
#pragma bank=3


//title screen image
extern unsigned char kwakwa_tiledata[];

void kwakwa_graphics() NONBANKED {
	SWITCH_ROM_MBC1(3);
	draw_image(kwakwa_tiledata);
}

void kwakwa_screen() NONBANKED {
	UBYTE pstart = 1, keys = 0;
	wait_vbl_done();
	disable_interrupts();
	DISPLAY_OFF;
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	ENABLE_RAM_MBC1;
	DISPLAY_ON;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (keys & (J_A|J_START)) {
			break;
		}
		kwakwa_graphics();

	}
	DISABLE_RAM_MBC1;
}
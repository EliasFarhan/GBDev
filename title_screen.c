#include <gb/gb.h>
#include <gb/drawing.h>
#pragma bank=4




void title_graphics(UBYTE pstart) {
	if (pstart) {
		gotogxy(5, 15);
		gprintf("Press Start");
	}
}
void title_screen() {
	UBYTE counter = 0, pstart = 1, keys = 0;
	wait_vbl_done();
	disable_interrupts();
	DISPLAY_OFF;
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	//ENABLE_RAM_MBC1;
	DISPLAY_ON;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		//if (keys & (J_A|J_START)) {
		//	break;
		//}
		counter++;
		if (counter == 40) {
			title_graphics(pstart);
			pstart = !pstart;
			counter = 0;
		}
	}
	//DISABLE_RAM_MBC1;
}

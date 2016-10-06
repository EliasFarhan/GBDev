#include <gb/gb.h>



//title screen image
extern unsigned char kwakwa_logo_tiledata[];
extern unsigned char kwakwa_logo_tilemap[];


void kwakwa_screen() NONBANKED {

	UBYTE pstart = 0;
	UBYTE keys = 0;
	UBYTE i,j;
	ENABLE_RAM_MBC1;
	wait_vbl_done();
	disable_interrupts();
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	DISPLAY_OFF;

	SWITCH_ROM_MBC1(3);
	set_bkg_data(0x00U, 0x68U, kwakwa_logo_tiledata);
	for(i = 0; i != 20; i++)
	{
		for(j = 0; j!= 18; j++)
		{
			set_bkg_tiles(i,j,1,1, &kwakwa_logo_tilemap[i*18+j]);
		}
	}
	SHOW_BKG;
	DISPLAY_ON;
	enable_interrupts();
	while(1) {
		wait_vbl_done();
		keys = joypad();
		if (pstart == 5U) {
			break;
		}
		pstart++;
	}
}

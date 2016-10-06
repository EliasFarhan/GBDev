#include <gb/gb.h>


//title screen image
extern unsigned char kwakwa_tiledata[];
extern unsigned char kwakwa_tilemap[];

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
	SWITCH_ROM_MBC1(3);
	set_bkg_data(0x00, 0x68, kwakwa_tiledata);
	for(i = 0; i != 20; i++)
	{
		for(j = 0; j!= 18; j++)
		{
			set_bkg_tiles(j,i,1,1, kwakwa_tilemap[i*18+j]);
		}
	}
	SHOW_BKG;
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

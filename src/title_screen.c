#include <gb/gb.h>
#include <gb/drawing.h>
#include <src/gbt_player.h>

//title screen image
extern unsigned char title_screen_gb_tiledata[];
extern unsigned char title_screen_gb_tilemap[];
extern const unsigned char * MainTheme_Data[];

void title_screen() NONBANKED 
{
	UBYTE pstart = 1, keys = 0;

	wait_vbl_done();
	disable_interrupts();
	HIDE_SPRITES;
	HIDE_WIN;
	HIDE_BKG;
	DISPLAY_OFF;
	SWITCH_ROM_MBC1(1);
	set_bkg_data(0U,131U,title_screen_gb_tiledata);
	set_bkg_tiles(0,0,20,18, title_screen_gb_tilemap);


	SPRITES_8x8;//TODO: why not 8x16?

	gbt_play(MainTheme_Data, 5, 7);
	gbt_loop(0x01U);

	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	enable_interrupts();
	while(1)
	{
		wait_vbl_done();
		keys = joypad();

		if (keys & (J_A|J_START))
		{
			break;
		}
		gbt_update();
	}
}

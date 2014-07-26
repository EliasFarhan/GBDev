/*
 * back.c
 *
 *  Created on: Jul 24, 2014
 *      Author: efarhan
 */
#include <gb/gb.h>
unsigned char TileLabel[] =
{
  0x18,0x3C,0x18,0x3C,0x58,0x3C,0x80,0x7F,
  0x01,0xFE,0x1A,0x3C,0x18,0x3C,0x18,0x3C
};
unsigned char TileMap[] = 
{
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0
};
#define MAXWINX   MAXWNDPOSX
#define MAXWINY   MAXWNDPOSY


void main()
{
	UBYTE i, j;
	disable_interrupts();
	DISPLAY_OFF;
	LCDC_REG = 0x67;
	/* Set palettes */
	 BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;


	/* First we put the data into the game
	 *
	 * set_bkg_data (
	 * 			UBYTE first_tile,
	 * 			UBYTE nb_tiles,
	 * 			unsigned char *data);
	 */
	set_bkg_data(0, 1, TileLabel);
	/*
	   * Second we draw the background
	   *
	   * Width  = 0x100 = 0x20 * 8
	   * Height = 0x100 = 0x20 * 8
	   */
	  for(i = 0; i < 32; i+=8)
	    for(j = 0; j < 32; j+=8)
	      /*
	       * void set_bkg_tiles(
	       * 			UBYTE x,
	       * 			UBYTE y,
	       * 			UBYTE w,
	       * 			UBYTE h,
	       * 			unsigned char *tiles);
	       */

	    	set_bkg_tiles(i, j, 8, 8, TileMap);


	  SCX_REG = 0;
	  SCY_REG = 0;
/*
--------------------------------------------------------------
	I don't know why, but if we put 0
	in the W[XY]_REG
	we don't see the background anymore
--------------------------------------------------------------
*/

	  WX_REG = MAXWNDPOSX;
	  WY_REG = MAXWNDPOSY;

	  DISPLAY_ON;
	  enable_interrupts();
	  while(1) {
		  /* Skip four VBLs (slow down animation) */
		  for(i = 0; i < 4; i++)
			  wait_vbl_done();
		  i = joypad();
		  /*SCX_REG += 1;
		  SCY_REG += 1;
		  WX_REG -= 1;
		  WY_REG -= 1;*/
	  }
}




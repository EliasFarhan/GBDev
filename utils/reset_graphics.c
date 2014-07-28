/* an empty line for the background, to reset graphics */
extern unsigned char cEMPTY[]; 

void empty_screen (void)
{
	UBYTE temp1;

	//DISPLAY_OFF;
	HIDE_BKG;
	HIDE_SPRITES;
	
	VBK_REG = 0;
	ENABLE_RAM_MBC1;

	for (temp1=0; temp1<40; temp1++)
	{
		move_sprite(temp1,0,200);
		set_sprite_prop (temp1,0);
	}

	SWITCH_ROM_MBC1(4);
	for (temp1=0; temp1<20; temp1++)
	{
		set_bkg_tiles (0,temp1,20,1,(unsigned char *) &cEMPTY[0]);   
		set_win_tiles (0,temp1,20,1,(unsigned char *) &cEMPTY[0]);   
		
		VBK_REG = 1;
		set_bkg_tiles (0,temp1,20,1,(unsigned char *) &cEMPTY[0]);   
		set_win_tiles (0,temp1,20,1,(unsigned char *) &cEMPTY[0]);   
		VBK_REG = 0;
	}
	SWITCH_ROM_MBC1(0);
	DISABLE_RAM_MBC1;
	move_bkg (0,0);
	
	SHOW_BKG;
	SHOW_SPRITES;
	//DISPLAY_ON;

}

void disable_APA()
{
	
	UINT8 i, blank = 0;
	disable_interrupts();
	empty_screen();
	for (i=0x00;i!=0xFF;++i) {
		
		remove_VBL(i);
		remove_LCD(i);
		
	}
	LCDC_REG = 0x18C0;
	mode(0xE00);
	enable_interrupts();
	
}

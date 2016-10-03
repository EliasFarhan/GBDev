#include <gb/gb.h>
#include <gb/sample.h>
#include <stdio.h>

UWORD backcolours[] =
{ 
32733,16714,15822,19648,
32733,16714,15822,19648,
32733,16714,15822,19648,
};


extern UBYTE musicdat[];
extern UBYTE musicdat2[];
extern UBYTE musicdat3[];
extern UBYTE musicdat4[];
extern UBYTE musicdat5[];
extern UBYTE musicdat6[];

void main()
{
    int WaveFrame = 0; int WaveF = 0;
    int Mode = 0;
	int v = 0;
 	if(_cpu == 0x11) set_bkg_palette(0, 2, backcolours); // if CGB
    
	puts("         ");
    puts("    GAME BOY PCM");	
    puts("       (gbdk)");	
	puts("--------------------");	
	puts("    GB/GBC demo");
	puts("         ");
	puts("4 bit PCM - 8192 Hz");
    puts("         ");	
	puts("  press B to play");
    puts("--------------------");	
	
	while(1)
	{
	
	   	if (joypad() & J_B){
		 puts("         ");
		 puts("  EMOTION BURST");
		 puts("  LOCOMOTION");
		 for (v = 0; v<4;v++){
		  SWITCH_ROM_MBC1(2);
		  play_sample(musicdat, 21900 / 32);
          SWITCH_ROM_MBC1(3);
		  play_sample(musicdat2, 21800 / 32);
		 }
		puts("         "); 
        puts("   By WATERFLAME");
		 for (v = 0; v<4;v++){
		  SWITCH_ROM_MBC1(4);
		  play_sample(musicdat3, 22000 / 32);
          SWITCH_ROM_MBC1(5);
		  play_sample(musicdat4, 21800 / 32);
		 } 
		 for (v = 0; v<4;v++){
		  SWITCH_ROM_MBC1(6);
		  play_sample(musicdat5, 21500 / 32);
          SWITCH_ROM_MBC1(7);
		  play_sample(musicdat6, 22200 / 32);
		 } 		 		 
		 SWITCH_ROM_MBC1(2);
		 play_sample(musicdat, 21900 / 32);
         SWITCH_ROM_MBC1(3);
		 play_sample(musicdat2, 21800 / 32);	 
		 
		 SWITCH_ROM_MBC1(2);
		 play_sample(musicdat, 21900 / 32);
         SWITCH_ROM_MBC1(3);
		 play_sample(musicdat2, 21800 / 32);

		 SWITCH_ROM_MBC1(4);
		 play_sample(musicdat3, 22000 / 32);
         SWITCH_ROM_MBC1(5);
		 play_sample(musicdat4, 21800 / 32);		 
		 
		 SWITCH_ROM_MBC1(2);
		 play_sample(musicdat, 21900 / 32);
         SWITCH_ROM_MBC1(3);
		 play_sample(musicdat2, 21800 / 32);		 	 
		 }		
	    delay(100);
        wait_vbl_done();	
    }		
		
	
}

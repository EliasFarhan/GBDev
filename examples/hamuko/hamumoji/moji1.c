#include <gb/gb.h>
#include <stdio.h>

#include "hamumoji.c"    // ƒnƒ€Žq•¶Žš‚Ìƒ^ƒCƒ‹ƒf�[ƒ^


void DISP_MOJI()
{
	gotoxy( 2, 2 );
	printf( "Hello World!" );

	gotoxy( 2, 4 );
	printf( "ÊÛ° Ü°ÙÄÞ¤" ); // ƒnƒ€Žq•¶Žš‚Í”¼ŠpƒJƒ^ƒJƒi‚Å�‘‚­
				// ¢¤£‚ÍŽg—p•p“x‚ª�­‚È‚¢‚Ì‚Å�@¢!£‚Æ•\Ž¦‚³‚ê‚é‚æ‚¤‚É‚µ‚Ä‚¢‚Ü‚·
}

void INIT()  // ‰æ–Ê‚Ì�‰Šú‰»
{
	printf( " " );     // ‰æ–Ê‚Ì�‰Šú‰»‚Ì‘O‚É�@‚±‚Ì1�s‚ª‚È‚¢‚Æ�@ƒnƒ€Žq•¶Žš‚à•¶Žš‰»‚¯‚µ‚Ü‚·

	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	set_bkg_data( 160, 65, hamumoji );    // ƒnƒ€Žq•¶Žš‚ÉŽg‚¤ƒ^ƒCƒ‹ƒf�[ƒ^�@160”Ô�`�@65–‡�@hamumoji�i‚Å�ì‚Á‚½ƒ^ƒCƒ‹�j‚ðƒZƒbƒg‚·‚é

	SHOW_BKG; 
	DISPLAY_ON;
	enable_interrupts();
}

void main()
{
	INIT();
	DISP_MOJI();

}


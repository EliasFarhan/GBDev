#include <gb/gb.h>
#include <stdio.h>

#include "hamumoji.c"   // ƒnƒ€Žq•¶Žš‚Ìƒ^ƒCƒ‹ƒf�[ƒ^

#define MOJI_MAX 15
// •¶‚Ìˆê”Ô�ÅŒã‚ÉNULL‚ª‚ ‚é‚Ì‚Å�@ŽÀ�Û‚ÉŽg‚¦‚é‚Ì‚Í14•¶Žš

void DISP_MOJI()
{
	UBYTE x, y, i;

	unsigned char first[MOJI_MAX] = "ÊÑºÓ¼ÞÊ ºÝÅÌ³Æ";  // ƒnƒ€Žq•¶Žš‚Í”¼ŠpƒJƒ^ƒJƒi‚Å�‘‚­
	unsigned char second[MOJI_MAX] = "Â¶³ºÄ¶Þ ÃÞ·Ï½¡"; // 14•¶ŽšˆÈ“à‚É‚·‚é
	unsigned char third[MOJI_MAX] = "Ë×¶ÞÅ¶Þ Â¶´Ù¯Ã";
	unsigned char fourth[MOJI_MAX] = "¶ÅØ ³Ú¼¸ÅØÏ½¡";

	x = y = 2;

		for( i = 0; i < MOJI_MAX; i++ ){     // ˆê•¶Žš‚¸‚Â�o‚Ä‚­‚é‚æ‚¤‚É‚·‚é‚½‚ß‚Ìƒ‹�[ƒv

			set_bkg_tiles( x + i, y, 1, 1, &first[i] );
			delay(100);      // ‘¬‚³‚Ì’²�ß
		}

		for( i = 0; i < MOJI_MAX; i++ ){

			set_bkg_tiles( x + i, y + 2, 1, 1, &second[i] );
			delay(100);
		}

		set_bkg_tiles( x, y + 6, MOJI_MAX, 1, third );
		set_bkg_tiles( x + 2, y + 8, MOJI_MAX, 1, fourth );

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


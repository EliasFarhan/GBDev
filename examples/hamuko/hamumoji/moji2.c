#include <gb.h>
#include <stdio.h>

#include "hamumoji.c"   // ハム子文字のタイルデータ

#define MOJI_MAX 15
// 文の一番最後にNULLがあるので　実際に使えるのは14文字


void DISP_MOJI()
{
	UBYTE x, y;

	unsigned char first[MOJI_MAX] = "ﾊﾑｺﾓｼﾞﾊ ｺﾝﾅﾌｳﾆ";  // ハム子文字は半角カタカナで書く
	unsigned char second[MOJI_MAX] = "ﾂｶｳｺﾄｶﾞ ﾃﾞｷﾏｽ｡"; // 14文字以内にする
	unsigned char third[MOJI_MAX] = "ﾋﾗｶﾞﾅｶﾞ ﾂｶｴﾙｯﾃ";
	unsigned char fourth[MOJI_MAX] = "ｶﾅﾘ ｳﾚｼｸﾅﾘﾏｽ｡";

	x = y = 2;

	set_bkg_tiles( x, y, MOJI_MAX, 1, first );
	set_bkg_tiles( x, y + 2, MOJI_MAX, 1, second );
	set_bkg_tiles( x, y + 6, MOJI_MAX, 1, third );
	set_bkg_tiles( x + 2, y + 8, MOJI_MAX, 1, fourth );

}

void INIT()  // 画面の初期化
{
	printf( " " );     // 画面の初期化の前に　この1行がないと　ハム子文字も文字化けします

	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	set_bkg_data( 160, 65, hamumoji );    // ハム子文字に使うタイルデータ　160番～　65枚　hamumoji（で作ったタイル）をセットする

	SHOW_BKG; 
	DISPLAY_ON;
	enable_interrupts();
}

void main()
{
	INIT();
	DISP_MOJI();

}


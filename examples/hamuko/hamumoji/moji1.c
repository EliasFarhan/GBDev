#include <gb.h>
#include <stdio.h>

#include "hamumoji.c"    // ハム子文字のタイルデータ


void DISP_MOJI()
{
	gotoxy( 2, 2 );
	printf( "Hello World!" );

	gotoxy( 2, 4 );
	printf( "ﾊﾛｰ ﾜｰﾙﾄﾞ､" ); // ハム子文字は半角カタカナで書く
				// ｢､｣は使用頻度が少ないので　｢!｣と表示されるようにしています
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


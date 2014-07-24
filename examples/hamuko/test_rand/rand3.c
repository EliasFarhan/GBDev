#include <gb.h>
#include <stdio.h>
#include <rand.h>    // 乱数を使う為のヘッダーファイル

#include "hamumoji.c"   // ハム子文字のタイルデータ

/*--------------------------------------------------------*/
void INIT();
void RANSUU_INIT();
void DISP_MESSAGE();

/*--------------------------------------------------------*/
fixed seed;  // 乱数の種
UBYTE r;     // 乱数

/*--------------------------------------------------------*/
void INIT()  // 画面の初期化
{
	printf( " " );

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

/*--------------------------------------------------------*/
void RANSUU_INIT() //乱数の初期化　このやり方はSDKのexampleフォルダの中にあります
{
	UBYTE x, y;
	x = y = 1;

	gotoxy( x, y ) ;
	printf("ﾊﾑｺﾉ ｺｳﾄﾞｳｦ") ;
	gotoxy( x, y + 2 );
	printf("ﾗﾝｽｳﾆﾖｯﾃ ｷﾒﾃﾐﾏｽ");
	gotoxy( x + 2, y + 5 );
	printf("[A]ﾎﾞﾀﾝｦ ｵｼﾃﾈ");
	gotoxy( x, y + 7 );
	printf("-----------------");

	waitpad(J_A);
	seed.b.l = DIV_REG;
	waitpadup();
	seed.b.h = DIV_REG;

	initarand(seed.w);   // 乱数の初期化

}

/*--------------------------------------------------------*/
void DISP_MESSAGE()   // rのとる値によって表示メッセージを変えてみる
{
	UBYTE x, y;
	x = 3, y = 10;

	gotoxy( x, y );
	printf("r = %u", r );
	gotoxy( x, y + 2 );
	    switch(r){
		case 0:
			printf("ﾊﾑｺﾊ ﾆｯｺﾘﾎﾎｴﾝﾀﾞ");
			break;
		case 1:
			printf("ﾊﾑｺﾊ ﾐｦﾏﾓｯﾃｲﾙ  ");
			break;
		case 2:
			printf("ﾊﾑｺﾊ ﾈﾑｯﾃｼﾏｯﾀ･･");
			break;
		case 3:
			printf("ﾊﾑｺﾊ ﾒｦｻﾏｼﾀ!   ");
			break;
		case 4:
			printf("ﾊﾑｺﾊ ｱｼｶﾞｶﾗﾏｯﾀ ");
			break;
	    }

}

/*--------------------------------------------------------*/
void main()
{
	UBYTE pad;

	INIT();
	RANSUU_INIT();

	for(;;){
		pad = joypad();

		r = rand() % 5;   // r のとる値は　0から4

		if( pad & J_A ){
			DISP_MESSAGE();
			waitpadup();
		}
	}

}


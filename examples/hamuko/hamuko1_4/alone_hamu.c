#include <gb.h>
#include <stdio.h>
#include <rand.h>  // 乱数を使う為のヘッダーファイル

#include "bgtile1.c"
#include "bgmap4.c"

#include "hamuko.c"     // ハム子のタイルデータ
#include "hamumoji.c"   // ハム子文字のタイルデータ

/*--------------------------------------------------------*/
void  SET_MOVE_HAMUKO();
void  OPENING_MESSAGE();
void  RANSUU_INIT();
void  INIT();
void  PATTERN_CHANGE();
void  DIRECT_RANSUU();
UBYTE AHEAD_KABE();
void  MOVE_HAMUKO();

/*--------------------------------------------------------*/
UBYTE hx, hy, hd, hp;

UBYTE hamuko_tile[4][2][4] =
{
	0, 1, 2, 3,       /* direct North */
	4, 5, 6, 7,

	8, 9, 10, 11,     /* direct East */
	12, 13, 14, 15,

	16, 17, 18, 19,   /* direct South */
	20, 21, 22, 23,

	24, 25, 26, 27,   /* direct West */
	28, 29, 30, 31
};

fixed seed;  // 乱数の種
UBYTE r;     // 乱数

/*--------------------------------------------------------*/
void SET_MOVE_HAMUKO()
{
	set_sprite_tile( 0, hamuko_tile[hd][hp][0] );
	set_sprite_tile( 1, hamuko_tile[hd][hp][1] );
	set_sprite_tile( 2, hamuko_tile[hd][hp][2] );
	set_sprite_tile( 3, hamuko_tile[hd][hp][3] );

	move_sprite( 0, hx * 8 + 8, hy * 8 + 16 );
	move_sprite( 1, hx * 8 + 8, hy * 8 + 24 );
	move_sprite( 2, hx * 8 + 16, hy * 8 + 16 );
	move_sprite( 3, hx * 8 + 16, hy * 8 + 24 );
}

/*--------------------------------------------------------*/
void OPENING_MESSAGE()
{
	UBYTE x, y;

	x = y = 1;

	gotoxy( x, y ) ;
	printf("ﾊﾑｺﾉ ﾎｳｺｳｦ") ;
	gotoxy( x, y + 2 );
	printf("ﾗﾝｽｳﾆﾖｯﾃ ｷﾒﾃﾐﾏｽ");
	gotoxy( x + 2, y + 5 );
	printf("[A]ﾎﾞﾀﾝｦ ｵｼﾃﾈ");    // 乱数の初期化の為に　Aボタンを押してもらうメッセージ
}

/*--------------------------------------------------------*/
void RANSUU_INIT() //乱数の初期化　このやり方はSDKのexampleフォルダの中にあります
{
	waitpad(J_A);
	seed.b.l = DIV_REG;
	waitpadup();
	seed.b.h = DIV_REG;

	initarand(seed.w);   // 乱数の初期化

}
/*--------------------------------------------------------*/
void INIT()
{
	UBYTE i;

	printf(" ");

	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	set_bkg_data( 0, 5, bgtile1 );
	set_bkg_data( 160, 65, hamumoji );    // ハム子文字に使うタイルデータ　160番～　65枚　hamumoji（で作ったタイル）をセットする

	set_sprite_data( 0, 32, hamuko );
	SPRITES_8x8;

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();

	//------------------------------乱数の初期化の為にオープニングにメッセージを追加
	OPENING_MESSAGE();
	RANSUU_INIT();
	//------------------------------

	set_bkg_tiles( 0, 0, bgmap4Width, bgmap4Height, bgmap4 );

	hx = hy = 1;
	hd = 2;
	hp = 0;

	SET_MOVE_HAMUKO();

	for( i = 0; i < 4; i++ ){
		set_sprite_prop( i, 0 );
	}

}

/*--------------------------------------------------------*/
void PATTERN_CHANGE()  // パターンを変更する
{
	hp = ( hp == 0 ) ? 1 : 0 ;  // パターンを表す変数hpが　0だったら1にする。そうじゃなかったら0
}

/*--------------------------------------------------------*/
void DIRECT_RANSUU()  // rが0の値をとった時に　ハム子の方向が変わる
{
	if( r == 0 ){
		switch(hd){
			case 0:
				hd = 1;
				break;
			case 1:
				hd = 2;
				break;
			case 2:
				hd = 3;
				break;
			case 3:
				hd = 0;
				break;
		}
	}
}

/*--------------------------------------------------------*/
UBYTE AHEAD_KABE()   // 前方に壁があるかどうか　あったら1を　なければ0を返す
{
	UWORD C1, C2;

	switch(hd){
		case 0:
			C1 = (UWORD)(hy - 1) * bgmap4Width + hx;
			C2 = C1 + 1;
			break;
		case 1:
			C1 = (UWORD)hy * bgmap4Width + (hx + 2);
			C2 = C1 + bgmap4Width;
			break;
		case 2:
			C1 = (UWORD)(hy + 2) * bgmap4Width + hx;
			C2 = C1 + 1;
			break;
		case 3:
			C1 = (UWORD)hy * bgmap4Width + (hx - 1);
			C2 = C1 + bgmap4Width;
			break;
	}

	if( *(bgmap4 + C1) != 0x00 || *(bgmap4 + C2) != 0x00 ) return 1;

	return 0;
}

/*--------------------------------------------------------*/
void MOVE_HAMUKO()
{
	if(AHEAD_KABE() == 0){  // 前方に壁がなければ進める
		switch(hd){
			case 0:
				hy--;
				break;
			case 1:
				hx++;
				break;
			case 2:
				hy++;
				break;
			case 3:
				hx--;
				break;
		}
	}else{
		r = 0;          // 前方に壁があった時は　rに0をいれる（向きを変える）
	}

	DIRECT_RANSUU();
	PATTERN_CHANGE();
	SET_MOVE_HAMUKO();
}

/*--------------------------------------------------------*/
void main()
{

	INIT();


	for(;;){

		r = rand() % 10;  // rのとる値は0から9までの10個の数　rがどの値になるかの確立が10%

		MOVE_HAMUKO();

		delay(300);
	}

}

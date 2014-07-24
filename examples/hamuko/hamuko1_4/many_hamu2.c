#include <gb.h>
#include <stdio.h>
#include <rand.h>  // 乱数を使う為のヘッダーファイル

#include "bgtile1.c"
#include "bgmap4.c"

#include "hamuko.c"     // ハム子のタイルデータ
#include "hamumoji.c"   // ハム子文字のタイルデータ

#define HAMU_MAX 4     // ハム子の最大人数

/*--------------------------------------------------------*/
void  SET_MOVE_HAMUKO();
void  OPENING_MESSAGE();
void  RANSUU_INIT();
void  INIT();
void  PATTERN_CHANGE(UBYTE i);
void  DIRECT_RANSUU(UBYTE i);

UBYTE AHEAD_KABE(UBYTE i);
UBYTE AHEAD_FRIEND(UBYTE i);
UBYTE CAN_MOVE(UBYTE i);

void  MOVE_HAMUKO(UBYTE i);

void  MOVE_MANY_HAMUKO();

/*----------------ハム子は複数になったので　構造体にする--*/
struct hamuko_s{
	UWORD x, y;      // ハム子の座標をUWORDにしておく
	UBYTE d, p;
}h[HAMU_MAX];
	
/*--------------------------------------------------------*/
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
	UBYTE i;
	
	for( i = 0; i < HAMU_MAX; i++ ){
		set_sprite_tile( i * 4, hamuko_tile[h[i].d][h[i].p][0] );
		set_sprite_tile( i * 4 + 1, hamuko_tile[h[i].d][h[i].p][1] );
		set_sprite_tile( i * 4 + 2, hamuko_tile[h[i].d][h[i].p][2] );
		set_sprite_tile( i * 4 + 3, hamuko_tile[h[i].d][h[i].p][3] );

		move_sprite( i * 4, h[i].x * 8 + 8, h[i].y * 8 + 16 );
		move_sprite( i * 4 + 1, h[i].x * 8 + 8, h[i].y * 8 + 24 );
		move_sprite( i * 4 + 2, h[i].x * 8 + 16, h[i].y * 8 + 16 );
		move_sprite( i * 4 + 3, h[i].x * 8 + 16, h[i].y * 8 + 24 );
	}
}

/*--------------------------------------------------------*/
void OPENING_MESSAGE()
{
	UBYTE x, y;

	x = y = 1;

	gotoxy( x, y ) ;
	printf("ﾊﾑｺﾀﾁ ｶｻﾅﾗﾅｸﾅﾘﾏｼﾀ") ;
	gotoxy( x, y + 2 );
	printf("ﾑｷﾊ ﾗﾝｽｳﾃﾞｷﾒﾃｲﾏｽ");
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

	h[0].x = h[0].y = 1;
	h[0].d = 1;
	h[0].p = 0;

	h[1].x = h[1].y = 4;
	h[1].d = 2;
	h[1].p = 0;

	h[2].x = h[2].y = 9;
	h[2].d = 1;
	h[2].p = 0;

	h[3].x = h[3].y = 12;
	h[3].d = 1;
	h[3].p = 0;

	SET_MOVE_HAMUKO();

	for( i = 0; i < 16; i++ ){     // 1人分4枚タイルを使ってて　それが4人分だから16
		set_sprite_prop( i, 0 );
	}

}

/*--------------------------------------------------------*/
void PATTERN_CHANGE(UBYTE i)  // パターンを変更する
{
	h[i].p = ( h[i].p == 0 ) ? 1 : 0 ;  // パターンを表す変数h[i].pが　0だったら1にする。そうじゃなかったら0
}

/*--------------------------------------------------------*/
void DIRECT_RANSUU(UBYTE i)  // rが0の値をとった時に　ハム子の方向が変わる
{
	if( r == 0 ){
		switch(h[i].d){
			case 0:
				h[i].d = 1;
				break;
			case 1:
				h[i].d = 2;
				break;
			case 2:
				h[i].d = 3;
				break;
			case 3:
				h[i].d = 0;
				break;
		}
	}
}

/*--------------------------------------------------------*/
UBYTE AHEAD_KABE(UBYTE i)   // 前方に壁があるかどうか　あったら1を　なければ0を返す
{
	UWORD C1, C2;

	switch(h[i].d){
		case 0:
			C1 = (UWORD)(h[i].y - 1) * bgmap4Width + h[i].x;
			C2 = C1 + 1;
			break;
		case 1:
			C1 = (UWORD)h[i].y * bgmap4Width + (h[i].x + 2);
			C2 = C1 + bgmap4Width;
			break;
		case 2:
			C1 = (UWORD)(h[i].y + 2) * bgmap4Width + h[i].x;
			C2 = C1 + 1;
			break;
		case 3:
			C1 = (UWORD)h[i].y * bgmap4Width + (h[i].x - 1);
			C2 = C1 + bgmap4Width;
			break;
	}

	if( *(bgmap4 + C1) != 0x00 || *(bgmap4 + C2) != 0x00 ) return 1;

	return 0;
}
/*--------------------------------------------------------*/
UBYTE AHEAD_FRIEND(UBYTE i)  // 前方に他のキャラがいるかどうか　いたら1を返す
{
	UBYTE hoka;
	UBYTE m = 0;  // 返り値

	for( hoka = 0; hoka < HAMU_MAX && m == 0; hoka++ ){

		if( i == hoka ) continue;  // 自分と他のキャラの重なりを見るのだから　自分同士の評価はしなくて大丈夫

		switch(h[i].d){
		case 0:
			if( h[i].y - 2 == h[hoka].y
				&& h[i].x - 1 <= h[hoka].x
				&& h[hoka].x <= h[i].x + 1 ) m = 1;  // 前方に他のキャラがいたらmに1をいれる
			break;
		case 1:
			if( h[i].x + 2 == h[hoka].x
				&& h[i].y - 1 <= h[hoka].y
				&& h[hoka].y <= h[i].y + 1 ) m = 1;
			break;
		case 2:
			if( h[i].y + 2 == h[hoka].y
				&& h[i].x - 1 <= h[hoka].x
				&& h[hoka].x <= h[i].x + 1 ) m = 1;
			break; 
		case 3:
			if( h[i].x - 2 == h[hoka].x
				&& h[i].y - 1 <= h[hoka].y
				&& h[hoka].y <= h[i].y + 1 ) m = 1;
			break;
		}
	}
	return m;   //  mを返す
}
/*--------------------------------------------------------*/
UBYTE CAN_MOVE(UBYTE i)  // 進めるかどうか？　壁があるかないかと　他キャラがいるかどうか　両方見る
{
	if( AHEAD_KABE(i) == 1 || AHEAD_FRIEND(i) == 1 ) return 1; // 1の時は進めない。
	return 0;
}

/*--------------------------------------------------------*/
void MOVE_HAMUKO(UBYTE i)
{
	if(CAN_MOVE(i) == 0){  // 前方になにもなければ進める
		switch(h[i].d){
			case 0:
				h[i].y--;
				break;
			case 1:
				h[i].x++;
				break;
			case 2:
				h[i].y++;
				break;
			case 3:
				h[i].x--;
				break;
		}
	}else{
		r = 0;          // 前方になにかがあった時は　rに0をいれる（向きを変える）
	}

	DIRECT_RANSUU(i);
	PATTERN_CHANGE(i);
	SET_MOVE_HAMUKO();
}

/*--------------------------------------------------------*/
void MOVE_MANY_HAMUKO()     // ハム子を全員動かす関数
{
	UBYTE hamu;

	for( hamu = 0; hamu != HAMU_MAX; hamu++ ){
		MOVE_HAMUKO(hamu);
	}
}

/*--------------------------------------------------------*/
void main()
{
	UBYTE i;

	INIT();

	for(;;){

		r = rand() % 10;  // rのとる値は0から9までの10個の数　rがどの値になるかの確立が10%
		
		MOVE_MANY_HAMUKO();

		delay(500);      // ハム子がたくさんいて忙しいので；；　ちょっとゆっくりめにした
	}

}

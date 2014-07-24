#include <gb.h>

#include "bgtile1.c"
#include "bgmap1.c"

#include "girl.c"

UBYTE gx, gy, gd, gp;  // x座標,　y座標,　方向,　パターン

UBYTE hamumi_tile[4][2][4] =  // 方角４つ　につき２パターンの絵が　タイル４枚で出来ている
{
	0, 1, 2, 3,        /* direct North */
	4, 5, 6, 7,

	8, 9, 10, 11,      /* direct East */
	12, 13, 14, 15,

	16, 17, 18, 19,    /* direct South */
	20, 21, 22, 23,

	24, 25, 26, 27,    /* direct West */
	28, 29, 30, 31
};

void SET_MOVE_SPRITE()  // スプライトタイルのセットと表示位置
{
	set_sprite_tile( 0, hamumi_tile[gd][gp][0] );
	set_sprite_tile( 1, hamumi_tile[gd][gp][1] );
	set_sprite_tile( 2, hamumi_tile[gd][gp][2] );
	set_sprite_tile( 3, hamumi_tile[gd][gp][3] );

	move_sprite( 0, gx * 8 + 8, gy * 8 + 16 );
	move_sprite( 1, gx * 8 + 8, gy * 8 + 24 );
	move_sprite( 2, gx * 8 + 16, gy * 8 + 16 );
	move_sprite( 3, gx * 8 + 16, gy * 8 + 24 );

}

void INIT()
{
	UBYTE i;

	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	set_bkg_data( 0, 5, bgtile1 );    
	set_bkg_tiles( 0, 0, bgmap1Width, bgmap1Height, bgmap1 );

	set_sprite_data( 0, 32, girl );
	SPRITES_8x8;

	gx = gy = 9;   // スプライトの座標の初期化
	gd = 0;   // スプライトの方向の初期化
	gp = 0;   // スプライトのパターンの初期化

	SET_MOVE_SPRITE();

	for( i = 0; i < 4; i++ ){          // スプライト4枚の表示を標準に設定
		set_sprite_prop( i, 0 );
	}

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
}

void main()
{

	INIT();

}

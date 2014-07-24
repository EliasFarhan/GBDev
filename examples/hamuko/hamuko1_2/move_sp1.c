#include <gb.h>

#include "bgtile1.c"
#include "bgmap1.c"

#include "girl.c"

UBYTE gx, gy, gd, gp;

UBYTE hamumi_tile[4][2][4] =
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

void SET_MOVE_SPRITE()
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

	gx = gy = 9;
	gd = 0;
	gp = 0;

	SET_MOVE_SPRITE();

	for( i = 0; i < 4; i++ ){
		set_sprite_prop( i, 0 );
	}

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
}

void PLUS_PAD()    // パッド入力（十字キー）で方向を変えれるようにする
{
	UBYTE pad;
	pad = joypad();  // パッドの状態をアクティブにする

	if( pad & ( J_UP | J_RIGHT | J_DOWN | J_LEFT )){
		if( pad & J_UP   ) gd = 0;      // もしもパッドが上に押されたら　方向を0にする（方向0は北）
		if( pad & J_RIGHT) gd = 1;
		if( pad & J_DOWN ) gd = 2;
		if( pad & J_LEFT ) gd = 3;
	}
}

void main()
{

	INIT();

	for(;;){
		SET_MOVE_SPRITE();
		PLUS_PAD();   // ループの中で パッド入力ができるようになる
	}

}

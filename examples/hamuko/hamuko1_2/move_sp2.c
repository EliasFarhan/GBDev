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

void PLUS_PAD()
{
	UBYTE pad;
	pad = joypad();
	if( pad & ( J_UP | J_RIGHT | J_DOWN | J_LEFT )){
		if( pad & J_UP   ) gd = 0;
		if( pad & J_RIGHT) gd = 1;
		if( pad & J_DOWN ) gd = 2;
		if( pad & J_LEFT ) gd = 3;
	}
}

void PATTERN_CHANGE()  // パターンを変更する
{
	gp = ( gp == 0 ) ? 1 : 0 ;  // パターンを表す変数gpが　0だったら1にする。そうじゃなかったら0
}

void main()
{
	INIT();

	for(;;){

		PLUS_PAD();
		SET_MOVE_SPRITE();
		PATTERN_CHANGE();   // ループの中で　gpが　1→0→1→0　を繰り返すことで歩いているように見える

		delay(300);
	}

}

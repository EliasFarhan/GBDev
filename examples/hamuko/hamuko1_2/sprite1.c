#include <gb.h>

#include "bgtile1.c"
#include "bgmap1.c"

#include "girl.c"  // スプライトに使うタイルデータ

void ABOUT_SPRITE()  // スプライトについての基本設定
{
	UBYTE gx, gy;   // スプライトキャラクタ（女の子）の座標

	set_sprite_data( 0, 32, girl );  // スプライトに使うタイルデータ0番～　32枚　girl（で作ったタイル）をセットする
	SPRITES_8x8;

	gx = gy = 9;       // スプライトの表示位置座標の初期化

        // 女の子一人を表示するのにスプライトタイルを4枚使っています

	set_sprite_tile( 0, 16 );  // スプライトタイル番号0番には　タイルデータgirlの16番をセットします
	set_sprite_tile( 1, 17 );
	set_sprite_tile( 2, 18 );
	set_sprite_tile( 3, 19 );

	move_sprite( 0, gx * 8 + 8, gy * 8 + 16 );  // スプライトタイル番号0番の表示位置は　(gx * 8 + 8, gy * 8 + 16) 
	move_sprite( 1, gx * 8 + 8, gy * 8 + 24 );
	move_sprite( 2, gx * 8 + 16, gy * 8 + 16 );
	move_sprite( 3, gx * 8 + 16, gy * 8 + 24 );

	set_sprite_prop( 0, 0 );  // スプライトの表示方法を標準に設定します
	set_sprite_prop( 1, 0 );
	set_sprite_prop( 2, 0 );
	set_sprite_prop( 3, 0 );

}

void INIT()
{
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	set_bkg_data( 0, 5, bgtile1 );    
	set_bkg_tiles( 0, 0, bgmap1Width, bgmap1Height, bgmap1 );

	ABOUT_SPRITE();   // スプライトについての基本設定

	SHOW_BKG;
	SHOW_SPRITES;     // スプライトを表示する
	DISPLAY_ON;
	enable_interrupts();
}

void main()
{

	INIT();

}

#include <gb/gb.h>

#include "bgtile1.c"  // 背景のタイルデータ
#include "bgmap1.c"   // 背景のマップデータ


void INIT()  // 画面の初期化
{
	disable_interrupts();
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	DISPLAY_OFF;

	set_bkg_data( 0, 5, bgtile1 );    // 背景に使うタイルデータ0番～　5枚　bgtile1（で作ったタイル）をセットする
	set_bkg_tiles( 0, 0, bgmap1Width, bgmap1Height, bgmap1 );　// マップデータbgmap1を背景にセットする
           // bgmap1Width, bgmap1Height は　bgmap1.c に定義されている
           // bgmap1Width 20  bgmap1Height 18

	SHOW_BKG;       // 背景を表示する
	DISPLAY_ON;
	enable_interrupts();
}

void main()
{

	INIT();

}

#include <gb/gb.h>
#include <stdio.h>
#include <gb/drawing.h>
#include <rand.h>  // —��”‚ðŽg‚¤ˆ×‚Ìƒwƒbƒ_�[ƒtƒ@ƒCƒ‹

#include "bgtile1.c"
#include "bgmap4.c"

#include "hamuko.c"     // ƒnƒ€Žq‚Ìƒ^ƒCƒ‹ƒf�[ƒ^
#include "hamumoji.c"   // ƒnƒ€Žq•¶Žš‚Ìƒ^ƒCƒ‹ƒf�[ƒ^

#define HAMU_MAX 5     // ƒnƒ€Žq‚Ì�Å‘å�l�”

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

/*----------------ƒnƒ€Žq‚Í•¡�”‚É‚È‚Á‚½‚Ì‚Å�@�\‘¢‘Ì‚É‚·‚é--*/
struct hamuko_s{
	UWORD x, y;      // ƒnƒ€Žq‚Ì�À•W‚ðUWORD‚É‚µ‚Ä‚¨‚­
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

fixed seed;  // —��”‚ÌŽí
UBYTE r;     // —��”

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
	printf("ÊÑºÀÁ ¶»Å×Å¸ÅØÏ¼À") ;
	gotoxy( x, y + 2 );
	printf("Ñ·Ê ×Ý½³ÃÞ·ÒÃ²Ï½");
	gotoxy( x + 2, y + 5 );
	printf("[A]ÎÞÀÝ¦ µ¼ÃÈ");    // —��”‚Ì�‰Šú‰»‚Ìˆ×‚É�@Aƒ{ƒ^ƒ“‚ð‰Ÿ‚µ‚Ä‚à‚ç‚¤ƒ�ƒbƒZ�[ƒW
}

/*--------------------------------------------------------*/
void RANSUU_INIT() //—��”‚Ì�‰Šú‰»�@‚±‚Ì‚â‚è•û‚ÍSDK‚ÌexampleƒtƒHƒ‹ƒ_‚Ì’†‚É‚ ‚è‚Ü‚·
{
	waitpad(J_A);
	seed.b.l = DIV_REG;
	waitpadup();
	seed.b.h = DIV_REG;

	initarand(seed.w);   // —��”‚Ì�‰Šú‰»

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
	set_bkg_data( 160, 65, hamumoji );    // ƒnƒ€Žq•¶Žš‚ÉŽg‚¤ƒ^ƒCƒ‹ƒf�[ƒ^�@160”Ô�`�@65–‡�@hamumoji�i‚Å�ì‚Á‚½ƒ^ƒCƒ‹�j‚ðƒZƒbƒg‚·‚é

	set_sprite_data( 0, 32, hamuko );
	SPRITES_8x8;

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();

	//------------------------------—��”‚Ì�‰Šú‰»‚Ìˆ×‚ÉƒI�[ƒvƒjƒ“ƒO‚Éƒ�ƒbƒZ�[ƒW‚ð’Ç‰Á
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

	for( i = 0; i < 16; i++ ){     // 1�l•ª4–‡ƒ^ƒCƒ‹‚ðŽg‚Á‚Ä‚Ä�@‚»‚ê‚ª4�l•ª‚¾‚©‚ç16
		set_sprite_prop( i, 0 );
	}

}

/*--------------------------------------------------------*/
void PATTERN_CHANGE(UBYTE i)  // ƒpƒ^�[ƒ“‚ð•Ï�X‚·‚é
{
	h[i].p = ( h[i].p == 0 ) ? 1 : 0 ;  // ƒpƒ^�[ƒ“‚ð•\‚·•Ï�”h[i].p‚ª�@0‚¾‚Á‚½‚ç1‚É‚·‚é�B‚»‚¤‚¶‚á‚È‚©‚Á‚½‚ç0
}

/*--------------------------------------------------------*/
void DIRECT_RANSUU(UBYTE i)  // r‚ª0‚Ì’l‚ð‚Æ‚Á‚½Žž‚É�@ƒnƒ€Žq‚Ì•ûŒü‚ª•Ï‚í‚é
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
UBYTE AHEAD_KABE(UBYTE i)   // ‘O•û‚É•Ç‚ª‚ ‚é‚©‚Ç‚¤‚©�@‚ ‚Á‚½‚ç1‚ð�@‚È‚¯‚ê‚Î0‚ð•Ô‚·
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
UBYTE AHEAD_FRIEND(UBYTE i)  // ‘O•û‚É‘¼‚ÌƒLƒƒƒ‰‚ª‚¢‚é‚©‚Ç‚¤‚©�@‚¢‚½‚ç1‚ð•Ô‚·
{
	UBYTE hoka;
	UBYTE m = 0;  // •Ô‚è’l

	for( hoka = 0; hoka < HAMU_MAX && m == 0; hoka++ ){

		if( i == hoka ) continue;  // Ž©•ª‚Æ‘¼‚ÌƒLƒƒƒ‰‚Ì�d‚È‚è‚ðŒ©‚é‚Ì‚¾‚©‚ç�@Ž©•ª“¯Žm‚Ì•]‰¿‚Í‚µ‚È‚­‚Ä‘å�ä•v

		switch(h[i].d){
		case 0:
			if( h[i].y - 2 == h[hoka].y
				&& h[i].x - 1 <= h[hoka].x
				&& h[hoka].x <= h[i].x + 1 ) m = 1;  // ‘O•û‚É‘¼‚ÌƒLƒƒƒ‰‚ª‚¢‚½‚çm‚É1‚ð‚¢‚ê‚é
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
	return m;   //  m‚ð•Ô‚·
}
/*--------------------------------------------------------*/
UBYTE CAN_MOVE(UBYTE i)  // �i‚ß‚é‚©‚Ç‚¤‚©�H�@•Ç‚ª‚ ‚é‚©‚È‚¢‚©‚Æ�@‘¼ƒLƒƒƒ‰‚ª‚¢‚é‚©‚Ç‚¤‚©�@—¼•ûŒ©‚é
{
	if( AHEAD_KABE(i) == 1 || AHEAD_FRIEND(i) == 1 ) return 1; // 1‚ÌŽž‚Í�i‚ß‚È‚¢�B
	return 0;
}

/*--------------------------------------------------------*/
void MOVE_HAMUKO(UBYTE i)
{
	if(CAN_MOVE(i) == 0){  // ‘O•û‚É‚È‚É‚à‚È‚¯‚ê‚Î�i‚ß‚é
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
		r = 0;          // ‘O•û‚É‚È‚É‚©‚ª‚ ‚Á‚½Žž‚Í�@r‚É0‚ð‚¢‚ê‚é�iŒü‚«‚ð•Ï‚¦‚é�j
	}

	DIRECT_RANSUU(i);
	PATTERN_CHANGE(i);
	SET_MOVE_HAMUKO();
}

/*--------------------------------------------------------*/
void MOVE_MANY_HAMUKO()     // ƒnƒ€Žq‚ð‘Sˆõ“®‚©‚·ŠÖ�”
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

		r = rand() % 10;  // r‚Ì‚Æ‚é’l‚Í0‚©‚ç9‚Ü‚Å‚Ì10ŒÂ‚Ì�”�@r‚ª‚Ç‚Ì’l‚É‚È‚é‚©‚ÌŠm—§‚ª10%
		
		MOVE_MANY_HAMUKO();

		delay(500);      // ƒnƒ€Žq‚ª‚½‚­‚³‚ñ‚¢‚Ä–Z‚µ‚¢‚Ì‚Å�G�G�@‚¿‚å‚Á‚Æ‚ä‚Á‚­‚è‚ß‚É‚µ‚½
	}

}

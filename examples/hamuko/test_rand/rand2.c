#include <gb.h>
#include <stdio.h>
#include <rand.h>    // 乱数を使う為のヘッダーファイル


/*--------------------------------------------------------*/
void RANSUU_INIT()  //乱数の初期化　このやり方はSDKのexampleフォルダの中にあります
{
  fixed seed;  // 乱数の種

	printf(" ");
	gotoxy( 2, 5 ) ;
	printf("Please push [A]") ;  // 「Aボタンを押してください」
	gotoxy( 2, 8 );
	printf("- for get seed -");  // 「乱数の種を得る為に」
	waitpad(J_A);
	seed.b.l = DIV_REG;
	waitpadup();
	seed.b.h = DIV_REG;

	initarand(seed.w);   // 乱数の初期化

}

/*--------------------------------------------------------*/
void main()
{
	UBYTE i, r1, r2;

	RANSUU_INIT();
	
	cls();

	// printf(" ");  RANSUU_INIT()という関数の中でprintfが既に使われているので　ここはなくても大丈夫

	for( i = 0; i < 10; i++ ){

		r1 = rand();   // r1は　呼んだ乱数そのもの
		r2 = r1 % 10;  // 呼んだ乱数を10で割った余りなので　r2のとる値は0から9
		
		gotoxy( 1, i );
		printf( "%u", r1 );

		gotoxy( 10, i );
		printf( "%u", r2 );

	}

}


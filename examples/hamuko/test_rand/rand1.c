#include <gb.h>
#include <stdio.h>
#include <rand.h>    // 乱数を使う為のヘッダーファイル


void main()
{
	UBYTE i, r1, r2;
	
	printf(" ");

	for( i = 0; i < 10; i++ ){

		r1 = rand();   // r1は　呼んだ乱数そのもの
		r2 = r1 % 10;  // 呼んだ乱数を10で割った余りなので　r2のとる値は0から9
		
		gotoxy( 1, i );
		printf( "%u", r1 );

		gotoxy( 10, i );
		printf( "%u", r2 );

	}

}


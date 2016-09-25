#include <gb/gb.h>
#include <stdio.h>


void main()
{
	UBYTE y;

	printf ( " " );

	for( y = 19; y > 3; y-- ){    

		cls();                   // ˆê‰ñ‚²‚Æ‚É‰æ–Ê‚ðƒNƒŠƒA

		gotoxy( 4, y );
		printf( "Presented by" );

		gotoxy( 7, y + 2 );
		printf( "Hamuko" );

		delay( 300 );              // ‘�‚·‚¬‚é‚Ì‚Å‘¬“x’²�ß

	} 

        // forƒ‹�[ƒv‚ª�I‚í‚Á‚½‚çˆÈ‰º‚ð•\Ž¦‚·‚é

	gotoxy( 5, y + 6 );
	printf( "Welcome to" );

	gotoxy( 2, y + 8 );
	printf( "** DEKIRUKANA **" );


}

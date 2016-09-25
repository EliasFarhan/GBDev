#include <gb/gb.h>
#include <stdio.h>


void main()
{
	UBYTE y;

	y = 4;

		printf( " " );

		gotoxy( 4, y );
		printf( "Presented by" );

		gotoxy( 7, y + 2 );
		printf( "Hamuko" );

		gotoxy( 5, y + 6 );
		printf( "Welcome to" );

		gotoxy( 2, y + 8 );
		printf( "** DEKIRUKANA **" );


}

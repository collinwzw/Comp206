#include <stdio.h>

int main()
{
	char c;
	float f;
	char string[100];

	printf( "Enter a letter, a number and a string: " );
	
	scanf( "%c %f %s", &c, &f, string );

	printf( "The letter was %c.\n", c );
	printf( "The number was %f.\n", f );
	printf( "The string was %s.\n", string );

	return 0;
}

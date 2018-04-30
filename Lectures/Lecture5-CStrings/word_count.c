/* 
 * FILE: word_count.c demonstrates that C strings can be viewed both as 
 *                    array and as pointer to char form. The while
 *                    condition tells us when the \0 terminates valid data.
 */

#include <stdio.h>

int main()
{
	char string[100] = "The quick brown fox jumped over the pile of ice.";

	char *pos = string;
	unsigned int words = 0;
	while(*pos){                                   // Note that the while condition becomes false when we hit \0
		if( *pos  == ' ' || *pos == '.' ){
			words++;
		}

		printf( "Processing character %c with words %d.\n", *pos, words );

		pos++;                                // Pointer addition moves us forward by 1 char in memory
	}

	printf( "There were %d words.\n", words );

	return 0;
}

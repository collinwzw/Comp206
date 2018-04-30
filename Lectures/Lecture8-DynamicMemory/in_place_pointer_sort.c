/***************************************************
* File: in_place_pointer_sort.c
*
* An example showing the use of pointers to
* pass normal variables "by reference" and 
* the use of double-pointers to pass pointers
* "by reference". It's important that you understand
* why the version that does not use pointers 
* as the function arguments will fail to sort the data.
* 
* Author: David Meger
*
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap( char *a, char *b ){
   char temp = *a;
   *a = *b;
   *b = temp;
}

void find_minimum( char *s, char **min_s )
{
	unsigned char min_val = 255;
	while( *s  ){
		if( *s <= min_val ){
			min_val = *s;
			*min_s = s;
		}
		s++;
	}
}

int main( int argc, char *argv[] )
{
	if( argc != 2 ){
		printf( "Usage: %s <string_to_sort>\n", argv[0] );
		return EXIT_FAILURE;
	}
	
	// Move through the string, sorting one character at a time
	char *next_spot_to_sort_ptr = argv[1];
	while( *next_spot_to_sort_ptr ){

		char *minimum_spot_ptr;
		find_minimum( next_spot_to_sort_ptr, &minimum_spot_ptr );
		swap( next_spot_to_sort_ptr, minimum_spot_ptr );
		next_spot_to_sort_ptr++;		
	}

	printf( "The sorted version is %s.\n", argv[1] );
	return EXIT_SUCCESS;
}

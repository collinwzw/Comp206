/* File: array_sizes.c 
 * Demonstrates the scary cases of trying to use sizeof() to determine 
 * array lengths in C. Only when the array is viewed as a constant-sized
 * type, like the int large_array[10] definition, can C properly tell us
 * its size. Once we use a pointer, or pass it as an argument, sizeof
 * will instead tell us only the length of the pointer (8 on 64-bit system).
 *
 */

#include <stdio.h>

void fn( int array[] ){

	printf( "The size of the array in the function is %lu.\n", sizeof(array));
}

int main( int argc, char *argv[] )
{
	printf( "The size of argv is %lu.\n", sizeof(argv) );
	
	int large_array[10];
	int small_array[2];

	printf( "The size of array is %lu.\n", sizeof(large_array) );
	printf( "The size of small array is %lu.\n", sizeof(small_array));


	fn(large_array);
	fn(small_array);
}

/*
 * File: write_file.c Opens a file specified as a command-line argument
 * waits for user input and enters the input line-by-line into the file.
 * 
 * Discussed during Lecture 5 - COMP 206 Winter 2018
 *
 */  

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
	if( argc < 2 ){
		printf( "Usage: %s <output_name>.\n", argv[0] );
		exit(-1);
	}

	FILE* fp = fopen( argv[1], "w" );
	if( fp == NULL ){
		printf( "%s failed to open file %s for writing. Check permissions.\n", argv[0], argv[1] );
		exit(-1);
	}

	printf( "Enter lines to place in file, %s. Use ctrl-d to end.\n", argv[1] );

	char user_input[100];

	while( fgets( user_input, 100, stdin ) ){
		fputs( user_input, fp );
	}

	fclose(fp);
}




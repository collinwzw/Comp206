/*
 * FILE: strcmp.c Provides two different ways to compute whether 
 *                two strings are equal. We want to think about 
 *                the differences and understand why compare_str
 *                is the one included in string.h
 * 
 * Shown in lecture Jan 25th, 2018
 *
 */

#include <stdio.h>

int compare_str( char *one, char *two ){
	
	while(*one && *two){

		if( *one != *two ){
			return 1;
		}
		one++;
		two++;
	}

	if( *one == *two )
	{
		return 0;
	}
	else{
		return 1;
	}
}

int compare_ptr( char *one, char *two ){

	if( one == two ){
		return 0;
	}
	else{
		return 1;
	}
}

int main(){

	char first_sentence[100]  =  "206 is the greatest course!";
	char second_sentence[100] =  "206 is the greatest course!";
	char *third_sentence      =  first_sentence;

	if( compare_ptr(first_sentence,second_sentence) == 0 ){
		printf( "First equals second.\n" );
	}

	if( compare_ptr(first_sentence,third_sentence) == 0 ){
		printf( "First equals third.\n" );
	}

	if( compare_ptr(third_sentence,second_sentence) == 0 ){
		printf( "Third equals second.\n" );
	}

	return 0;
}

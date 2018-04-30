/* 
 * File: input_basics.c - A beginning example of user interaction.
 * 
 * Demonstrates the fgets function, which reads up to a specified number of 
 * characters from a file, which can include std input. This loop
 * is similar to that which the Linux shell might use to interact with the user.
 * 
 * Shown in COMP 206 Lecture 5
 *
 */

#include<stdio.h>

int main(){

	char string[100];

	printf( "Enter your command: ");
	while(fgets( string, 100, stdin )){
		printf("User's input was: %s", string );
		printf("Enter your command: ");
	}
}




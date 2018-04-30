/* FILE: create_heap_data.c is an example from the C bootcamp on
 *       passing pointer addresses into functions which 
 *       allocate heap memory and set it to initial values.
 *       
 *       It should be a helpful example for understanding how to do
 *       Assignment 2 Question 1.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fn( int** fn_int, char** fn_str ){

   *fn_int = (int*)malloc(sizeof(int));
   **fn_int = 6;

   *fn_str = (char*)malloc(100*sizeof(char));

   strcpy( *fn_str, "Hello, world!" );

}

int main(){

   int *main_int;
   char *main_str; 

   fn( &main_int, &main_str );

   printf( "After fn: main_int is %d and main_str is %s.\n", *main_int, main_str );

   main_str[0] = 'J';
   *main_int = 8;
   
   printf( "Main was able to change main_int to %d and main_str to %s.\n", *main_int, main_str ); 
   return 0;
}

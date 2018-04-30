/* FILE: bmp_collage.c is provided as part of COMP 206 A2. Do not modify this file.
 *       Its purpose is to test that you have implemented bmp_collage correctly for
 *       Question 3. When you're finished, the output of this program should match
 *       the examples in the assignment document.
 */

#include <stdio.h>
#include <stdlib.h>
#include "A2_bmp_helpers.h"

int main( int argc, char* argv[] ){

  if( argc != 4 && argc != 6 ){
    printf( "bmp_collage must be run with parameters that allow two images to be collaged.\nUsage: $ %s <bmp_input1> <bmp_input2> <bmp_result> [top_offset] [left_offset], where [param] indicates optional\n", argv[0] );
    exit(EXIT_FAILURE);
  }
  
  int top_offset, left_offset;
  
  if( argc == 6 ){
    top_offset = atoi(argv[4]);
    left_offset = atoi(argv[5]);
  } 
  else {
    top_offset = 0;
    left_offset = 0;
  }
  
  // NOTE: This is the line that executes the bmp_collage function. It shows how your code will be called.
  int return_code = bmp_collage( argv[1], argv[2], argv[3], top_offset, left_offset );
  
  if( return_code )
    printf( "bmp_collage function returned an error.\n" );
  else
    printf( "bmp_collage operation completed correctly!\n" );
    
  return return_code;
}


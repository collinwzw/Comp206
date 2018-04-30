/***************************************************
* File: macro_debugging.c
*
* This simple example shows how the pre-preocesor
* can easily be used to make our lives easier when 
* debuging programs. 
*
* Try compiling with and without -DDEBUG and notice
* the difference in behaviour.
* 
* Author: David Meger
*
***************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
    #define debug(x,y) printf(x,y)
#else
   #define debug(x,y) /* Nothing here indicates it's compiled out */
#endif

int main()
{

	int a = 3;

	debug("The value of a is %d.\n", a );

	return EXIT_SUCCESS;
}


/* File: signals.c Produces a program that refuses to die when you type ctrl-c.
 *       The interrupt signal is handled by simply printing to the screen.
 *       Note that the handler can be run multiple times (as many as you hit ctrl-c)
 *       even though it is not actually called anywhere in the main.
 *
 *       How is it executed? By the operating system's signal handling features.
 * 
 *       Shown in class March 29th, 2018.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int sigaction( int signum, const struct sigaction *act, struct sigaction *oldact );

void handler(int code){
	fprintf( stderr, "Signal %d caught\n", code );
}

int main(){

	struct sigaction newact;
	newact.sa_handler = handler;
	newact.sa_flags = 0;
	sigemptyset( &newact.sa_mask);
	sigaction(SIGINT, &newact, NULL );

	int i = 0;
	for( ; ; ){
		if(( i++ % 50000000 ) == 0 ){
			fprintf( stderr, "." );
		}
	}

	return 0;

}

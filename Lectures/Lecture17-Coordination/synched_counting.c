/* File: synched_counting.c creates a child process and then has both
 *       the parent and the child count to 200.
 *       Each process waits on the semaphore that is posted to
 *       by the opposite side, keeping them always within 1
 *       number. The outcome is fair, alternating counting.
 * 
 *       Although the exmaple is simple, re-use this pattern! 
 *       Imagine how the section between semaphores can also be
 *       used to read/write files, compute math, etc, based on 
 *       the guaranteed fairness.
 *
 *       compile by typing "$ gcc synched_counting.c -lpthread"
 *
 *       Shown in class March 29th, 2018.
 */

#include  <stdio.h>
#include  <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100

sem_t *s1;
sem_t *s2;

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];
     
     s1 = sem_open( "first", O_CREAT, 0666, 1 );
     s2 = sem_open( "second", O_CREAT, 0666, 0 );

     int x = fork();
     pid = getpid();
     for (i = 1; i <= MAX_COUNT; i++) {
     
          if( x == 0 ){
            sem_wait( s1);
          }
          else{
            sem_wait( s2 );
          }
          
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf));
          
          if( x == 0 ){
            sem_post( s2);
          }
          else{
            sem_post( s1 );
          }
     } 
}


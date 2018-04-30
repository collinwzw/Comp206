#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int x = fork();
    if (x == -1) {
        perror("fork");
        return(1);
    } else if (x == 0) {
        /* child */
        execl("/bin/ls", "ls", (char *)NULL);
        perror("/bin/ls");
        return(1);
    } else {
        /* parent */
        int status, pid;
        pid = wait(&status);
        printf("pid %d exit status %d\n", pid, WEXITSTATUS(status));
        return(0);
    }
}


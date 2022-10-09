#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

void goodbye(int);

int main(int argc, char *argv[]) {
    pid_t ppid = getpid();
    int rc = fork();
    
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("Hallo\n");
        kill(ppid, SIGINT);
    } else {
        // parent 
        signal(SIGINT, goodbye);
        sleep(1);
    }
    return 0;
}

void goodbye(int signal)
{
        printf("Goodbye\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        close(STDOUT_FILENO);
        printf("hello I am child\n");
    } else {
        // parent
        int rc_wait = wait(NULL);
        printf("hello I am parent\n");
    }
    return 0;
}
    
// only parent can print in terminal because child closed STDOUT, only closed for its caller(child) process
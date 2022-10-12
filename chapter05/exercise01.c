#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("befor calling Child %d\n", x);
        x = 200;
        printf("hello, I am child (pid:%d) and have x %d\n", (int) getpid(), x);
    } else { // parent goes down this path (main)
        printf("befor calling Parent %d\n", x);
        x = 300;
        printf("hello, I am parent of %d(pid:%d) and have x %d\n",
        rc, (int) getpid(), x);
    }
    return 0;
}

/* at the beginning of each process, the variable x will be 100 */
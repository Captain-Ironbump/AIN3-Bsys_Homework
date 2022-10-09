#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int file = open("./exercise02.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if (file < 0) {
        return -1;
    }
    
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("file child %d\n", file);
        write(file, "file child\n", 11);
    } else {
        // parent goes down this path 
        printf("file parent %d\n", file);
        write(file, "file parent\n", 12);
    }
    return 0;
}
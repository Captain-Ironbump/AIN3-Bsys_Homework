#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char buf;
    int pipefd[2];

    /* Erstellung der Pipe */
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /* Child 1 (New Process) Initialisierung */
    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    /* Child 2 (New Process) Initialisierung */
    int rc2 = fork();
    if (rc2 < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0 && rc2 > 0) {
        // child process 1
        printf("Child 1\n");
        close(pipefd[0]);   // close unused read end

        /*Test*/
        //printf("Argv: %s\n", argv[1]);

        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          // Reader will see EOF
        wait(NULL);                // Wait
        exit(EXIT_SUCCESS);

    } else if (rc1 > 0 && rc2 == 0) {
        // child process 2
        printf("Child 2\n");
        close(pipefd[1]);   // close unused write end
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);


    } else if (rc1 > 0 && rc2 > 0) {
        /* Parent process */
        printf("Hello, I am parent\n");
    }
    return 0;
}
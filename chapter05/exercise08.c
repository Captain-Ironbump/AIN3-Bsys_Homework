#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    char buf;
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process 1
        close(pipefd[0]);   // close unused read end
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          // Reader will see EOF
        wait(NULL);                // Wait
        exit(EXIT_SUCCESS);

    } else if (rc == 1) {
        // child process 2
        close(pipefd[1]);   // close unused write end
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
        

    } else {
        // parent
        printf("Hello\n");
        printf("%d\n", pipefd[0]);
    }
    return 0;
}
    
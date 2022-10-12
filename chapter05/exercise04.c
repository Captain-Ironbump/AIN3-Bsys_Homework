#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>


int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("hello, I am child (pid:%d)\n", (int) getpid());

        char *binaryPath = "/bin/ls";
        char *binaryPath2 = "/bin/bash";
        char *arg1 = "-lh";
        char *arg2 = "/home";
        char *arg3 = "-c";
        char *arg4 = "echo \"Visit $HOSTNAME:$PORT from your browser.\"";
        char *command = "ls";
        char *const env[] = {"HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};
        char *args[] = {binaryPath, "-lh", "/home", NULL};
        char *args2[] = {command, "-lh", "/home", NULL};
        char *const args3[] = {binaryPath2, "-c", "echo \"Visit $HOSTNAME:$PORT from your browser.\"", NULL};

        execl(binaryPath, binaryPath, arg1, arg2, NULL);
        /* takes the binaryPath fpr the first and second argument, then the argument you wnat to pass the executable followed by NULL */
        //execle(binaryPath2, binaryPath2, arg3, arg4, NULL, env);
        /* just like execl() but you can use your own environment variables */
        //execlp(command, command, arg1, arg2, NULL);
        /* uses PATH enviroment, full path not needed, just using the executable file */
        //execv(binaryPath, args);
        /* passing the arguments in a NULL terminated array */
        //execvp(command, args2);
        /* like execv, but PATH enviroment is used */
        //execve(binaryPath2, args3, env);
        /* like execle (environment variables) + arguments in arrays */

    } else {
        // parent process
        int rc_wait = wait(NULL);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
            rc, rc_wait, (int) getpid());
    }
    return 0;
}

// Quelle: https://linuxhint.com/exec_linux_system_call_c/
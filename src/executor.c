// executor.c
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/executor.h"

void execute_command(char **args, int background) {
    pid_t pid = fork();
    if (pid == 0) {

        for (int i =0; args[i] != NULL; i ++) {
            if (args[i][0] == '$') {
                char *value = getenv(args[i] + 1);

                if (value) {
                    args[i] = value;
                }
            }            
        }

        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        if (!background)
            wait(NULL);
        else
            printf("Background process started with PID : %d\n", pid);
    } else {
        perror("Fork failed");
    }
}

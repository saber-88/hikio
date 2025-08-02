// executor.c
#include "../include/executor.h"
#include "fcntl.h"
#include <limits.h>
// #include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
extern char **environ;

void execute_command(char **args, int background) {
  pid_t pid = fork();
  if (pid == 0) {

    int allocated[40] = {0};
    char *left_args[40], *right_args[40];
    int pipe_index = -1;

    for (int i = 0; args[i] != NULL; i++) { // Env Variable Expansion
      if (args[i][0] == '$') {
        char *value = getenv(args[i] + 1);
        if (value) {
          args[i] = strdup(value);
        } else {
          args[i] = strdup("");
        }
        allocated[i] = 1;
      }
    }

    for (int i = 0; args[i]; i++) { // Tilde Expansion
      if (args[i][0] == '~') {
        char *home = getenv("HOME");
        if (home) {
          char expanded[PATH_MAX];
          snprintf(expanded, sizeof(expanded), "%s%s", home, args[i] + 1);
          if (allocated[i]) {
            free(args[i]);
          }
          args[i] = strdup(expanded);
        } else {
          args[i] = strdup("");
        }
        allocated[i] = 1;
      }
    }

    for (int i = 0; args[i] != NULL; i++) {

      if (strcmp(args[i], "|") == 0) {
        if (args[i + 1] == NULL || i == 0) {
          fprintf(stderr,
                  "hikio: syntax error near unexpected token `newline'\n");
          exit(1);
        }
        pipe_index = i;
        int l = 0;
        for (l = 0; l < pipe_index; l++) {
          left_args[l] = args[l];
        }
        left_args[l] = NULL;
        int j = 0;
        for (int k = pipe_index + 1; args[k] != NULL; k++) {
          right_args[j++] = args[k];
        }
        right_args[j] = NULL;

        int fd[2];
        if (pipe(fd) == -1) {
          perror("pipe");
          exit(1);
        }

        args[pipe_index] = NULL;

        pid_t left_fork = fork();

        if (left_fork == 0) {
          close(fd[0]);
          dup2(fd[1], STDOUT_FILENO);
          close(fd[1]);
          execvp(left_args[0], left_args);
          perror("exec left");
          exit(1);
        }

        pid_t right_fork = fork();
        if (right_fork == 0) {
          close(fd[1]);
          dup2(fd[0], STDIN_FILENO);
          close(fd[0]);
          execvp(right_args[0], right_args);
          perror("exec right");
          exit(1);
        }

        close(fd[0]);
        close(fd[1]);
        waitpid(left_fork, NULL, 0);
        waitpid(right_fork, NULL, 0);

        for (int i = 0; args[i] != NULL; i++) {
          if (allocated[i]) {
            free(args[i]);
          }
        }
        exit(0);
        return; 

      } else if (strcmp(args[i], ">") == 0) {
        if (args[i + 1] == NULL) {
          fprintf(stderr,
                  "hikio: syntax error near unexpected token `newline'\n");
          exit(1);
        }
        int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[i] = NULL;
        break;

      } else if (strcmp(args[i], ">>") == 0) {
        if (args[i + 1] == NULL) {
          fprintf(stderr,
                  "hikio: syntax error near unexpected token `newline'\n");
          exit(1);
        }
        int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[i] = NULL;
        break;

      } else if (strcmp(args[i], "<") == 0) {
        if (args[i + 1] == NULL) {
          fprintf(stderr,
                  "hikio: syntax error near unexpected token `newline'\n");
          exit(1);
        }
        int fd = open(args[i + 1], O_RDONLY);
        if (fd < 0) {
          perror("hikio: input file open failed");
          exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        args[i] = NULL;
        break;
      }
    }

    execvp(args[0], args);
    perror("exec failed");
    for (int i = 0; args[i] != NULL; i++) {
      if (allocated[i]) {
        free(args[i]);
      }
    }
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

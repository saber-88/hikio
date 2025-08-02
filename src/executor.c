// executor.c
#include "../include/executor.h"
#include "fcntl.h"
#include <limits.h>
#include <stdatomic.h>
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

    for (int i = 0; args[i] != NULL; i++) {
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
    

    for (int i = 0; args[i]; i++) {
      if (args[i][0] == '~') {
        char *home = getenv("HOME");
        if (home) {
          char expanded [PATH_MAX];
          sprintf(expanded, "%s%s", home, args[i] + 1);
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
      if (strcmp(args[i], ">") == 0) {
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
    for (int i = 0 ; args[i] != NULL ; i++) {
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

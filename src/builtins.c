
// builtins.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/builtins.h"

int handle_builtin(char **args, char *hist_path, int *exit_shell) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            if (args[1][0] == '~') {
                char temp[1024];
                snprintf(temp, sizeof(temp), "%s%s", getenv("HOME"), args[1] + 1);
                chdir(temp);
            } else {
                chdir(args[1]);
            }
        }
        return 1;

    } else if (strcmp(args[0], "pwd") == 0) {
        char buffer[1024];
        getcwd(buffer, sizeof(buffer));
        printf("%s\n", buffer);
        return 1;

    } else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "q") == 0) {
        *exit_shell = 1;
        return 1;

    } else if (strcmp(args[0], "help") == 0) {
        printf("\nAvailable commands:\n");
        printf("  cd [dir]    - change directory\n");
        printf("  pwd         - print working directory\n");
        printf("  help        - show help\n");
        printf("  exit/q      - exit shell\n");
        return 1;

    } else if (strcmp(args[0], "clear") == 0) {
        // printf("\033[H\033[J");
        system("clear && tput reset");
        return 1;
    }

    return 0; // Not a builtin
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "prompt.h"
#include "builtins.h"
#include "executor.h"
#include "history.h"
#include <autocomplete.h>

#define MAX_TOKENS 40

int main() {
    char hist_path[1024];
    snprintf(hist_path, sizeof(hist_path), "%s/.hikio_history", getenv("HOME"));
    init_history(hist_path);
    init_autocomplete();

    int exit_shell = 0;

    while (!exit_shell) {
        char *prompt = show_prompt();
        char *input = readline(prompt);
        free(prompt);

        if (!input || strlen(input) == 0) {
            free(input);
            continue;
        }

        add_history(input);

        char *tokens[MAX_TOKENS];
        int i = 0;
        char *token = strtok(input, " ");
        while (token && i < MAX_TOKENS - 1) {
            tokens[i++] = token;
            token = strtok(NULL, " ");
        }
        tokens[i] = NULL;

        int background = 0;
        if (i > 0 && strcmp(tokens[i - 1], "&") == 0) {
            background = 1;
            tokens[i - 1] = NULL;
        }

        if (!handle_builtin(tokens, hist_path, &exit_shell)) {
            execute_command(tokens, background);
        }

        free(input);
    }

    save_history(hist_path);
    return 0;
}


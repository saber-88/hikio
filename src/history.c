#include <stdio.h>        
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/history.h"

void init_history(const char *hist_path) {
    read_history(hist_path);
}

void save_history(const char *hist_path) {
    write_history(hist_path);
}
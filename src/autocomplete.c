#include <stdio.h>
#include <../include/autocomplete.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void init_autocomplete(){
  rl_attempted_completion_function = command_completion;
}

char **command_completion(const char * text , int start , int end){
  return rl_completion_matches(text, command_generator);
}

char *command_generator(const char *text , int state){

  static DIR *dir;
  static struct dirent *entry;
  static int len;

  if (!state) {
    dir = opendir(".");
    len = strlen(text);
  }


  while ((entry = readdir(dir)) != NULL) {
    if (strncmp(entry->d_name, text, len) == 0) {
        return strdup(entry->d_name);
    }
  }

  closedir(dir);
  return NULL;
}
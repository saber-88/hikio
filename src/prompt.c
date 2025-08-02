#include "../include/prompt.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define HOSTNAME_SIZE 256

char *show_prompt() {

  char cwd[PATH_MAX];
  char hostname[HOSTNAME_SIZE];
  char *username = getenv("USER");
  const char *home_path = getenv("HOME");
  char *prompt = NULL;

  if (!username || !home_path) {
    username = "Unknown";
    home_path = "/";
  }

  if (getcwd(cwd, sizeof(cwd) )==NULL) {
    perror("getcwd");
    return NULL;
  }

  if (gethostname(hostname, sizeof(hostname)) == -1) {
    perror("hostname");
    return NULL;
  }


  if (strncmp(cwd, home_path, strlen(home_path)) == 0) {
    asprintf(&prompt,
             "\n[\033[1;34m%s\033[1;31m@%s \033[1;32m~%s\033[0m]\033[1;31m \n> "
             "\033[0m",
             username, hostname, cwd + strlen(home_path));
  } else {
    asprintf(&prompt,
             "\n\033[1;32m[%s@%s \033[1;34m%s\033[0m]\033[1;33m > \033[0m\n",
             username, hostname, cwd);
  }

  return prompt;
}
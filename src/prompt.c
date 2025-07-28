#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/prompt.h"


char * show_prompt(){
  
  char cwd[1024];
  char hostname[30];
  char * username = getenv("USER");

  getcwd(cwd, sizeof(cwd));
  gethostname(hostname, sizeof(hostname));

  char * display_path = NULL;


  char home_path[1024];
  snprintf(home_path, sizeof(home_path), "/home/%s",username);

  if (strncmp(cwd, home_path, strlen(home_path))==0) {
    asprintf(&display_path, "\n[\033[1;34m%s\033[1;31m@%s \033[1;32m~%s\033[0m]\033[1;31m > \033[0m",username,hostname,cwd + strlen(home_path));
  }
  else {
    asprintf(&display_path, "\n\033[1;32m[%s@%s \033[1;34m%s\033[0m]\033[1;33m > \033[0m",username,hostname,cwd);
  }
  return display_path;
}
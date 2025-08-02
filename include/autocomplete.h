#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

void init_autocomplete(void);
char **command_completion(const char *text, int start, int end);
char *command_generator(const char *text, int state);

#endif
#ifndef DB_UTIL_H
#define DB_UTIL_H
#include "Command.h"

void print_prompt();
int parse_input(char *input, Command_t *cmd);

#endif

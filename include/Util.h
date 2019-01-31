#ifndef DB_UTIL_H
#define DB_UTIL_H
#include "Command.h"

void print_prompt();
int parse_input(char *input, Command_t *cmd);
void handle_builtin_cmd(Command_t *cmd);
int handle_query_cmd(Command_t *cmd);

#endif

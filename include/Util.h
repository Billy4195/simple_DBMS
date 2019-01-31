#ifndef DB_UTIL_H
#define DB_UTIL_H
#include "Command.h"
#include "Table.h"

void print_prompt();
void print_user(User_t *user);
int parse_input(char *input, Command_t *cmd);
void handle_builtin_cmd(Command_t *cmd);
int handle_query_cmd(Table_t *table, Command_t *cmd);
int handle_insert_cmd(Table_t *table, Command_t *cmd);
int handle_select_cmd(Table_t *table, Command_t *cmd);

#endif

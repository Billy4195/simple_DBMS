#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include "Command.h"
#include "Table.h"

void print_prompt() { printf("db > "); }

/*
 * This function received an output argument
 * Return: category of the command
 */
int parse_input(char *input, Command_t *cmd) {
    char *token;
    token = strtok(input, " \n");
    if (!strncmp(token, ".exit", 5)) {
        cmd->type = BUILT_IN_CMD;
    } else if (!strncmp(token, "insert", 6)) {
        cmd->type = QUERY_CMD;
    }
    while (token != NULL) {
        add_Arg(cmd, token);
        token = strtok(NULL, " ");
    }
    return cmd->type;
}

void handle_builtin_cmd(Command_t *cmd) {
    if (!strncmp(cmd->args[0], ".exit", 5)) {
        exit(0);
    } else {

    }
}

int handle_query_cmd(Table_t *table, Command_t *cmd) {
    if (!strncmp(cmd->args[0], "insert", 6)) {
        handle_insert_cmd(table, cmd);
        return INSERT_CMD;
    } else {
        return UNRECOG_CMD;
    }
}

int handle_insert_cmd(Table_t *table, Command_t *cmd) {
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include "Command.h"
#include "Table.h"

void print_prompt() { printf("db > "); }

void print_user(User_t *user) {
    printf("(%d, %s, %s, %d", user->id, user->name, user->email, user->age);
}

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

/*
 * The return value is the number of rows insert into table
 * If the insert operation success, then change the input arg
 * `cmd->type` to INSERT_CMD
 */
int handle_insert_cmd(Table_t *table, Command_t *cmd) {
    int ret = 0;
    User_t *user = command_to_User(cmd);
    if (user) {
        ret = add_User(table, user);
        if (ret > 0) {
            cmd->type = INSERT_CMD;
        }
    }
    return ret;
}

/*
 * The return value is the number of rows select from table
 * If the select operation success, then change the input arg
 * `cmd->type` to SELECT_CMD
 */
int handle_select_cmd(Table_t *table, Command_t *cmd) {
    size_t idx;
    for (idx = 0; idx < table->len; idx++) {
        print_user((table->users)+idx);
    }
    cmd->type = SELECT_CMD;
    return table->len;
}


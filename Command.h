#ifndef COMMAND_H
#define COMMAND_H

enum { 
    UNRECOG_CMD,
    BUILT_IN_CMD,
    QUERY_CMD,
};

typedef struct Command {
    unsigned char type;
    char **args;
    size_t args_len;
    size_t args_cap;
} Command_t;

Command_t* new_Command();
int add_Arg(Command_t *cmd, char *arg);
void free_Command(Command_t *cmd);

#endif

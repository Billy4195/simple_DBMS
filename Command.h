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
} Command_t;

Command_t* new_Command();
void free_Command(Command_t *cmd);

#endif

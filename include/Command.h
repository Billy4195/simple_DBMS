#ifndef COMMAND_H
#define COMMAND_H

enum { 
    UNRECOG_CMD,
    BUILT_IN_CMD,
    QUERY_CMD,
};

enum {
    INSERT_CMD = 100,
    SELECT_CMD,
};

typedef struct {
    char name[256];
    int len;
    unsigned char type;
} CMD_t;

extern CMD_t cmd_list[];

typedef struct Command {
    unsigned char type;
    char **args;
    size_t args_len;
    size_t args_cap;
} Command_t;

Command_t* new_Command();
int add_Arg(Command_t *cmd, const char *arg);
void cleanup_Command(Command_t *cmd);

#endif

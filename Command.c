#include <stdlib.h>
#include "Command.h"

Command_t* new_Command() {
    Command_t *cmd = (Command_t*) malloc(sizeof(Command_t));
    cmd->type = UNRECOG_CMD;
    cmd->args = NULL;
    return cmd;
}

/*
 * TODO: This func should free the allocated memory
 */
void free_Command(Command_t *cmd) {

}

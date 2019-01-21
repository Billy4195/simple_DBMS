#include <assert.h>
#include <stdlib.h>
#include "Command.h"

void test_new_Command();

int main() {
    test_new_Command();
    return 0;
}

void test_new_Command() {
    Command_t *cmd = new_Command();
    assert(cmd->type == UNRECOG_CMD);
    assert(cmd->args == NULL);
    assert(cmd->args_len == 0);
    assert(cmd->args_cap == 0);
}

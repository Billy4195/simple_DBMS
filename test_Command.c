#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Command.h"

void test_new_Command();
void test_add_Arg();

int main() {
    test_new_Command();
    test_add_Arg();
    return 0;
}

void test_new_Command() {
    Command_t *cmd = new_Command();
    assert(cmd->type == UNRECOG_CMD);
    assert(cmd->args == NULL);
    assert(cmd->args_len == 0);
    assert(cmd->args_cap == 0);
}

void test_add_Arg() {
    Command_t *cmd = new_Command();
    int ret = add_Arg(cmd, "test1");
    if (ret == 0) {
        assert(cmd->args != NULL);
        assert(!strncmp(cmd->args[0], "test1", 5));
        assert(cmd->args_len == 1);
        assert(cmd->args_cap == 5);

        add_Arg(cmd, "test2");
        add_Arg(cmd, "test3");
        add_Arg(cmd, "test4");
        add_Arg(cmd, "test5");
        add_Arg(cmd, "test6");

        assert(cmd->args != NULL);
        assert(!strncmp(cmd->args[5], "test6", 5));
        assert(cmd->args_len == 6);
        assert(cmd->args_cap == 10);
    } else {
        assert(cmd->args = NULL);
    }
}

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Command.h"
#include "gtest/gtest.h"

TEST(testCommand, testNewCommand) {
    Command_t *cmd = new_Command();
    ASSERT_EQ(cmd->type, UNRECOG_CMD);
    ASSERT_EQ(cmd->args, nullptr);
    ASSERT_TRUE(cmd->args_len == 0);
    ASSERT_TRUE(cmd->args_cap == 0);
}


TEST(testCommand, testAddArg) {
    Command_t *cmd = new_Command();
    int ret = add_Arg(cmd, "test1");
    if (ret == 0) {
        ASSERT_NE(cmd->args, nullptr);
        ASSERT_TRUE(!strncmp(cmd->args[0], "test1", 5));
        ASSERT_TRUE(cmd->args_len == 1);
        ASSERT_TRUE(cmd->args_cap == 5);

        add_Arg(cmd, "test2");
        add_Arg(cmd, "test3");
        add_Arg(cmd, "test4");
        add_Arg(cmd, "test5");
        add_Arg(cmd, "test6");

        ASSERT_NE(cmd->args, nullptr);
        ASSERT_EQ(strncmp(cmd->args[5], "test6", 5), 0);
        ASSERT_TRUE(cmd->args_len == 6);
        ASSERT_TRUE(cmd->args_cap == 10);
    } else {
        ASSERT_EQ(cmd->args, nullptr);
    }
}


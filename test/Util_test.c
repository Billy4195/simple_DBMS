#include "gtest/gtest.h"
#include "Util.h"

TEST(testUtil, testHandleQueryCmdInsert) {
    char const *args[] = { "insert" };
    Command_t cmd = { QUERY_CMD, (char**)args, 1, 1 };
    int ret;
    ret = handle_query_cmd(&cmd);
    ASSERT_EQ(ret, INSERT_CMD);
}

TEST(testUtil, testHandleQueryCmdFail) {
    char const *args[] = { "unknown" };
    Command_t cmd = { QUERY_CMD, (char**)args, 1, 1 };
    int ret;
    ret = handle_query_cmd(&cmd);
    ASSERT_EQ(ret, UNRECOG_CMD);
}


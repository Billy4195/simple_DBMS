#include "gtest/gtest.h"
#include "Util.h"
#include "Table.h"

TEST(testUtil, testHandleQueryCmdInsert) {
    Table_t *table = new_Table();
    char const *args[] = { "insert" };
    Command_t cmd = { QUERY_CMD, (char**)args, 1, 1 };
    int ret;
    ret = handle_query_cmd(table, &cmd);
    ASSERT_EQ(ret, INSERT_CMD);
}

TEST(testUtil, testHandleQueryCmdFail) {
    Table_t *table = new_Table();
    char const *args[] = { "unknown" };
    Command_t cmd = { QUERY_CMD, (char**)args, 1, 1 };
    int ret;
    ret = handle_query_cmd(table, &cmd);
    ASSERT_EQ(ret, UNRECOG_CMD);
}

TEST(testUtil, testHandleInsertCmd) {
    Table_t *table = new_Table();
    char const *args[] = { "insert", "1", "user1", \
            "user1@example.com", "21" };
    Command_t cmd = { QUERY_CMD, (char **)args, 5, 5 };
    int ret;
    ret = handle_insert_cmd(table, &cmd);
    ASSERT_NE(ret, 0);
    ASSERT_EQ(cmd.type, INSERT_CMD);
}


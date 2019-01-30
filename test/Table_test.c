#include "gtest/gtest.h"
#include "Table.h"

TEST(testTable, testNewTable) {
    Table_t *table = new_Table();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->capacity, MAX_TABLE_SIZE);
    ASSERT_EQ(table->len, 0);
    ASSERT_NE(table->users, nullptr);
}


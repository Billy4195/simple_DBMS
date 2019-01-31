#include "gtest/gtest.h"
#include "Table.h"
#include "User.h"

TEST(testTable, testNewTable) {
    Table_t *table = new_Table();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->capacity, MAX_TABLE_SIZE);
    ASSERT_EQ(table->len, 0);
    ASSERT_NE(table->users, nullptr);
}

TEST(testTable, testAddUserSuc) {
    Table_t *table = new_Table();
    ASSERT_NE(table, nullptr);

    User_t user = { 1, "First User", "first@example.com", 21 };

    ASSERT_EQ(add_User(table, &user), 1);
    ASSERT_EQ(table->capacity, MAX_TABLE_SIZE);
    ASSERT_EQ(table->len, 1);
    ASSERT_EQ(table->users[0].id, user.id);
    ASSERT_STREQ(table->users[0].name, user.name);
    ASSERT_STREQ(table->users[0].email, user.email);
    ASSERT_EQ(table->users[0].age, user.age);
}

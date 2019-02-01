#include <stdio.h>
#include <sys/stat.h>
#include "gtest/gtest.h"
#include "Table.h"
#include "User.h"

TEST(testTable, testNewTable) {
    Table_t *table = new_Table(NULL);
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->capacity, MAX_TABLE_SIZE);
    ASSERT_EQ(table->len, 0);
    ASSERT_NE(table->users, nullptr);
    ASSERT_EQ(table->fp, nullptr);
}

TEST(testTable, testNewTableWithFile) {
    char file_name[] = "./test/test.db";
    Table_t *table = new_Table(file_name);
    struct stat st;

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->capacity, MAX_TABLE_SIZE);
    ASSERT_EQ(table->len, 0);
    ASSERT_NE(table->users, nullptr);
    ASSERT_NE(table->fp, nullptr);
    fclose(table->fp);
    remove(file_name);
    ASSERT_NE(stat(file_name, &st), 0);
}

TEST(testTable, testNewTableWithOldFile) {
    char file_name[] = "./test/test.db";
    FILE *fp;
    Table_t *table;
    struct stat st;
    User_t users[] = {
        { 1, "user1", "user1@example.com", 20},
        { 2, "user2", "user2@example.com", 22},
    };

    fp = fopen(file_name, "wb");
    fwrite((void*)users, sizeof(User_t), 2, fp);
    fclose(fp);
    {
        struct stat st;
        ASSERT_EQ(stat(file_name, &st), 0);
        ASSERT_EQ(st.st_size, sizeof(User_t)*2);
    }

    table = new_Table(file_name);
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->capacity, MAX_TABLE_SIZE);
    ASSERT_EQ(table->len, 2);
    ASSERT_NE(table->users, nullptr);
    ASSERT_NE(table->fp, nullptr);
    fclose(table->fp);
    remove(file_name);
    ASSERT_NE(stat(file_name, &st), 0);
}

TEST(testTable, testAddUserSuc) {
    Table_t *table = new_Table(NULL);
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

TEST(testTable, testAddUserFail) {
    Table_t *table = new_Table(NULL);
    User_t user = { 1, "First User", "first@example.com", 21 };
    ASSERT_NE(add_User(NULL, NULL), 1);
    ASSERT_NE(add_User(table, NULL), 1);
    ASSERT_NE(add_User(NULL, &user), 1);
}

TEST(testTable, testAddUserFull) {
    Table_t *table = new_Table(NULL);
    User_t user = { 1, "user", "user@example.com", 20 };
    size_t idx;
    int ret = 0;
    for (idx = 0; idx < MAX_TABLE_SIZE; idx++) {
        ret = add_User(table, &user);
        ASSERT_EQ(ret, 1);
        ASSERT_EQ(table->len, idx+1);
        ASSERT_TRUE(table->len <= MAX_TABLE_SIZE);
    }
    ret = add_User(table, &user);
    ASSERT_NE(ret, 1);
    ASSERT_TRUE(table->len <= MAX_TABLE_SIZE);
}

TEST(testTable, testArchiveTable) {
    char file_name[] = "./test/test.db";
    Table_t *table;
    struct stat st;
    User_t user = { 1, "user", "user@example.com", 20 };
    const size_t insert_count = 5;
    size_t idx;
    int ret;

    ASSERT_NE(stat(file_name, &st), 0);

    table = new_Table(file_name);
    for (idx = 0; idx < insert_count; idx++) {
        ret = add_User(table, &user);
        EXPECT_EQ(ret, 1);
        EXPECT_EQ(table->len, idx+1);
    }
    ret = archive_table(table);
    EXPECT_EQ(ret, insert_count);
    EXPECT_EQ(stat(file_name, &st), 0);
    EXPECT_EQ(st.st_size, sizeof(User_t)*insert_count);

    fclose(table->fp);
    remove(file_name);
    ASSERT_NE(stat(file_name, &st), 0);
}

TEST(testTable, testArchiveOldTable) {
    char file_name[] = "./test/test.db";
    FILE *fp;
    Table_t *table;
    struct stat st;
    User_t users[] = {
        { 1, "user1", "user1@example.com", 20},
        { 2, "user2", "user2@example.com", 22},
    };
    User_t user = { 3, "user", "user@example.com", 20 };
    const size_t insert_count = 5;
    size_t idx;
    int ret;

    fp = fopen(file_name, "wb");
    fwrite((void*)users, sizeof(User_t), 2, fp);
    fclose(fp);
    {
        struct stat st;
        ASSERT_EQ(stat(file_name, &st), 0);
        ASSERT_EQ(st.st_size, sizeof(User_t)*2);
    }

    table = new_Table(file_name);
    for (idx = 0; idx < insert_count; idx++) {
        ret = add_User(table, &user);
        EXPECT_EQ(ret, 1);
    }
    ret = archive_table(table);
    EXPECT_EQ(ret, (int)insert_count+2);
    EXPECT_EQ(stat(file_name, &st), 0);
    EXPECT_EQ(st.st_size, sizeof(User_t)*(insert_count+2));

    fclose(table->fp);
    remove(file_name);
    ASSERT_NE(stat(file_name, &st), 0);
}


#include "gtest/gtest.h"
#include "User.h"

TEST(testUser, testNewUser) {
    User_t *user = new_User();
    ASSERT_NE(user, nullptr);
    ASSERT_EQ(user->id, 0);
    ASSERT_EQ(strlen(user->name), 0);
    ASSERT_EQ(strlen(user->email), 0);
    ASSERT_EQ(user->age, 0);
}

#include <gtest/gtest.h>
#include "user.h"

TEST(UserTest, CreateUserTest) {
    User user("testuser", "password123");
    EXPECT_EQ(user.getUsername(), "testuser");
    EXPECT_FALSE(user.getPasswordhash().empty());
}

int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

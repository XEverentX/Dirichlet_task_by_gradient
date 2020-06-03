// Copyright 2020 Lebedev Alexander

#include <gtest/gtest.h>

class CanTest : public ::testing::Test {
 protected:
    double epsilon = 0.0000001;
};

TEST_F(CanTest, CanTest) {
    // Arrange
    int x = 5;

    // Act
    int y = 5;

    // Assert
    ASSERT_EQ(x, y);
}

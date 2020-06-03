// Copyright 2020 Lebedev Alexander

#include <gtest/gtest.h>

#include <task.hpp>
#include <statistic.hpp>
#include <util.hpp>

#include <vector>

class simpleTest : public ::testing::Test {
 protected:
    double epsilon = 0.0001;
};

TEST_F(simpleTest, scalarMul) {
    // Arrange
    std::vector<std::vector<double>> v1 = {{0., 1.}, {2., 0.}};
    std::vector<std::vector<double>> v2 = {{7.5, 3.}, {4.2, 0.}};
    double expected = 11.4;

    // Act
    double result1 = util::scalarMul(v1, v2);
    double result2 = util::scalarMul(v2, v1);

    // Assert
    ASSERT_EQ(expected, result1);
    ASSERT_EQ(expected, result2);
}

TEST_F(simpleTest, fIsValid) {
    // Arrange
    double expected = -6.18309;
    Task task;

    // Act
    double result = task.getF(0.2, 0.5);

    // Assert
    ASSERT_NEAR(expected, result, epsilon);
}

TEST_F(simpleTest, uIsValid) {
    // Arrange
    double expected = 1.100199473393;
    Task task;

    // Act
    double result = task.getU(0.2, 0.5);

    // Assert
    ASSERT_NEAR(expected, result, epsilon);
}

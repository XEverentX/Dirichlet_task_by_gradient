// Copyright 2020 Lebedev Alexander

#include <gtest/gtest.h>

#include <task.hpp>
#include <statistic.hpp>
#include <util.hpp>

#include <vector>
#include <algorithm>

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

TEST_F(simpleTest, borderCheckerIsValid) {
    // Arrange
    int    n = 8;
    int    m = 4;
    double a = 0., b = 1., c = 0., d = 1.;

    Task task;
    task.setBoundaries(a, b, c, d);
    task.setPartition(n, m);

    std::vector<std::pair<int, int>> expected;
    std::vector<std::pair<int, int>> result;

    for (int i = 0; i <= 8; i++)
    {
        expected.push_back({i, 0});
        expected.push_back({i, 4});
        if ((i > 1 && i < 5) || i == 7)
        {
            for (int j = 1; j < 4; j++)
            {
                expected.push_back({i, j});
            }
        }
    }

    for (int j = 1; j <= 3; j++)
    {
        expected.push_back({0, j});
        expected.push_back({8, j});
    }

    std::sort(expected.begin(), expected.end());

    // Act
    for (int i = 0; i <= 8; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            if (!task.checkCoeficient(i, j))
            {
                result.push_back({i, j});
            }
        }
    }
    std::sort(result.begin(), result.end());

    // Assert
    ASSERT_EQ(expected.size(), result.size());
    ASSERT_EQ(expected, result);
}

TEST_F(simpleTest, simpleDiscripancyTest) {
    // Arrange
    int    n = 8;
    int    m = 4;
    double a = 0., b = 1., c = 0., d = 1.;
    double h = (b - a) / n;
    double k = (d - c) / m;

    Task task;
    task.setBoundaries(a, b, c, d);
    task.setPartition(n, m);

    double expected = (1. + task.getU(0.25, 0.25)) / (h * h) + 1. / (k * k) + task.getF(0.125, 0.25);

    std::vector<std::vector<double>> v(n + 1, std::vector<double>(m + 1));

    // Act
    task.getDiscrepancy(v);

    // Assert
    ASSERT_NEAR(expected, v[1][1], 0.01);
}

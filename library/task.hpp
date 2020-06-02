// Copyright 2020 Lebedev Alexander

#ifndef LIBRARY_TASK_HPP_
#define LIBRARY_TASK_HPP_

#include <statistic.hpp>

#include <functional>

class Task final
{
 public:
    Task();

    Task(const Task &other) = default;

    Task(Task &&other) = default;

    ~Task() = default;

    void setBoundaries(double n_a, double n_b, double n_c, double n_d) noexcept;

    void setPartition(int n_n, int n_m);

    auto solve(double minEps, int maxCount) -> Statistic;

 private:
    double k2;
    double h2;
    double a2;
    double a;
    double b;
    double c;
    double d;
    int    n;
    int    m;

    std::function<double(double, double)> u;
    std::function<double(double, double)> f;

    std::vector<std::vector<double>> v;
};

#endif  // LIBRARY_TASK_HPP_

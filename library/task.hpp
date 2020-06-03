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

    auto getF(double x, double y) const noexcept-> double;

    auto getU(double x, double y) const noexcept -> double;

    auto checkCoeficient(int i, int j) const noexcept-> bool;

    auto isBoard(int i, int j) const noexcept -> bool;

    auto getDiscrepancy(std::vector<std::vector<double>> &v) const noexcept -> void;

 private:
    auto getX(int index) const -> double;

    auto getY(int index) const -> double;

    inline void calcParams();

    double a;
    double b;
    double c;
    double d;
    double h;
    double k;
    double a2;
    double h2;
    double k2;
    int    n;
    int    m;
    int    nk;
    int    mk;

    std::function<double(double, double)> u;
    std::function<double(double, double)> f;

    std::vector<std::vector<double>> v;
};

#endif  // LIBRARY_TASK_HPP_

// Copyright 2020 Lebedev Alexander

#ifndef LIBRARY_STATISTIC_HPP_
#define LIBRARY_STATISTIC_HPP_

#include <vector>
#include <string>

class Statistic final
{
 public:
    Statistic() = default;

    Statistic(const Statistic &other) = default;
    
    Statistic(Statistic &&other) = default;

    ~Statistic() = default;

    std::string getReference() const;

 private:
    int    n;
    int    m;
    int    maxCount;
    int    count;
    double minEps;
    double eps;
    double discrepancyNorm;
    double inaccuracy;
    double initialDiscrepancyNorm;
    double maxDiscrepancyX;
    double maxDiscrepancyY;

    std::vector<std::vector<double>> realValue;
    std::vector<std::vector<double>> solvedValue;
    std::vector<std::vector<double>> diffValue;
};

#endif  // LIBRARY_STATISTIC_HPP_

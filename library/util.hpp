// Copyright 2020 Lebedev Alexander

#ifndef LIBRARY_UTIL_HPP_
#define LIBRARY_UTIL_HPP_

#include <vector>

namespace util 
{
    template<typename T>
    inline auto sqr(T value) -> T
    {
        return value * value;
    }

    template<typename T>
    inline auto norm(const std::vector<T> &v) -> T
    {
        T result = 0;
        for (auto x : v)
        {
            result += sqr(x);
        }
        return sqrt(result);
    }

    inline auto scalarMul(const std::vector<std::vector<double>> &v1,
                          const std::vector<std::vector<double>> &v2) -> double
    {
        double result = 0;
        int size = v1.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < v1[0].size(); j++)
            {
                result += v1[i][j] * v2[i][j];
            }
        }

        return result;
    }
}  // namespace util

#endif  // LIBRARY_UTIL_HPP_

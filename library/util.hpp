// Copyright 2020 Lebedev Alexander

#ifndef LIBRARY_UTIL_HPP_
#define LIBRARY_UTIL_HPP_

#include <vector>
#include <cmath>

namespace util 
{
    template<typename T>
    inline auto sqr(T value) -> T
    {
        return value * value;
    }

    template<typename T>
    inline auto norm(const std::vector<std::vector<T>> &v) -> T
    {
        T result = 0;
        int size = v.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < v[0].size(); j++)
            {
                result += sqr(v[i][j]);
            }
        }
        return std::sqrt(result);
    }
}  // namespace util

#endif  // LIBRARY_UTIL_HPP_

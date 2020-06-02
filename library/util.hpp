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

    template<typename T>
    inline auto scalarMul(const std::vector<T> &v1, const std::vector<T> &v2)
    {
        auto result = 0;
        int size = v1.size();
        for (int i = 0; i < size; i++)
        {
            result += v1[i] * v2[i];
        }

        return result;
    }
}  // namespace util

#endif  // LIBRARY_UTIL_HPP_

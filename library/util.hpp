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
    inline auto norm(std::vector<T> v) -> T
    {
        T result = 0;
        for (auto x : v)
        {
            result += sqr(x);
        }
        return sqrt(result);
    }
}  // namespace util

#endif  // LIBRARY_UTIL_HPP_

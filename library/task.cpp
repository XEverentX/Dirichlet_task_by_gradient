#include "task.hpp"
#include <util.hpp>

#include <stdexcept>
#include <cmath>

Task::Task()
{
    a = b = c = d = 0.;
    n = m = 0;
    v = std::vector<std::vector<double>>(m + 1, std::vector<double>(n + 1));

    u = [] (double x, double y) -> double {
        return exp(util::sqr(sin(x * y * M_PI)));
    };

    f = [] (double x, double y) -> double {
        return x;
    };
}

void Task::setBoundaries(double n_a, double n_b, double n_c, double n_d) noexcept
{
    a = n_a;
    b = n_b;
    c = n_c;
    d = n_d;
}

void Task::setPartition(int n_n, int n_m)
{
    if (n_n % 8)
    {
        throw std::invalid_argument("n should be a multiple of 8");
    }
    if (n_m % 4)
    {
        throw std::invalid_argument("m should be a multiple of 4");
    }
    n = n_n;
    m = n_m;
}

auto Task::solve(double minEps, int maxCount) -> Statistic
{
    Statistic result(n, m, minEps, maxCount);

    double h = (b - a) / n;
    double k = (d - c) / m;

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            result.realValue[i][j] = u(a + h * j, c + k * i);
        }
    }
    return result;
}

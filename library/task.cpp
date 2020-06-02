#include "task.hpp"
#include <util.hpp>

#include <stdexcept>
#include <cmath>
#include <iostream>

Task::Task()
{
    a = b = c = d = h = k = a2 = h2 = k2 = 0.;
    n = m = nk = mk = 0;
    

    u = [] (double x, double y) -> double {
        return exp(util::sqr(sin(x * y * M_PI)));
    };

    // -2*(pi^2)*exp((sin(pi*x*y))^2)*((2*(sin(pi*x*y)^2)+1)*(cos(pi*x*y)^2)-(sin(pi*x*y)^2))*((x^2)+(y^2))

    f = [] (double x, double y) -> double {
        return -2. * util::sqr(M_PI) * util::sqr(exp((sin(M_PI * x * y)))) *
               ((2. * util::sqr(sin(M_PI * x * y)) + 1) * 
                util::sqr(cos(M_PI * x * y)) - util::sqr(sin(M_PI* x * y))) * 
               (util::sqr(x) + util::sqr(y));
    };
}

void Task::setBoundaries(double n_a, double n_b, double n_c, double n_d) noexcept
{
    a = n_a;
    b = n_b;
    c = n_c;
    d = n_d;

    calcParams();
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

    calcParams();
}

inline void Task::calcParams()
{
    nk = n / 8;
    mk = m / 4;

    h = (b - a) / n;
    k = (d - c) / m;

    h2 = util::sqr((1. / h));
    k2 = util::sqr((1. / k));
    a2 = -2. * (h2 + k2);

    v = std::vector<std::vector<double>>(n + 1, std::vector<double>(m + 1));

    for (int j = 0; j <= m; j++)
    {
        for (int i = 0; i <= n; i++)
        {
            if (isBoard(i, j))
            {
                v[i][j] = u(getX(i), getY(j));
            }
            v[i][j] = u(getX(i), getY(j));
        }
    }
}

auto Task::getX(int index) const -> double
{
    return a + h * index;
}

auto Task::getY(int index) const -> double
{
    return c + k * index;
}

auto Task::checkCoeficient(int i, int j) const noexcept-> bool
{
    if ((j >= mk && j <= 3 * mk && ((i >= 2 * nk && i <= 4 * nk) || (i >= 7 * nk))) ||
        i == 0 || j == 0 || i == n || j == m)
    {
        return false;
    }

    return true;
}

auto Task::isBoard(int i, int j) const noexcept-> bool
{
    if (((j == mk || j == 3 * mk) && ((i >= 2 * nk && i <= 4 * nk) || (i >= 7 * nk)) || 
        ((j >= mk && j <= 3 * mk) && (i == 2 * nk || i == 4 * nk || i == 7 * nk))) ||
        i == 0 || j == 0 || i == n || j == m)
    {
        return true;
    }

    return false;
}

auto Task::getDiscrepancy(std::vector<std::vector<double>> &h) const noexcept -> void
{
    for (int j = 1; j < m; j++)
    {
        for (int i = 1; i < n; i++)
        {
            if (checkCoeficient(i, j))
            {   
                h[i][j] = a2 * v[i][j] + 
                            h2 * (v[i + 1][j] + v[i - 1][j]) +
                            k2 * (v[i][j + 1] + v[i][j - 1]) +
                            f(getX(i), getY(j));
            } else
            {
                h[i][j] = v[i][j];
            }
            
        }
    }
}

auto Task::solve(double minEps, int maxCount) -> Statistic
{
    int    dx[]   = {0, 0, 1, 0, -1};
    int    dy[]   = {0, 1, 0, -1, 0};
    double coef[] = {a2, k2, h2, k2, h2};
    double eps = 0.;
    int    count = 0;
    std::vector<std::vector<double>> ah(n + 1, std::vector<double>(m + 1));
    std::vector<std::vector<double>> h(n + 1, std::vector<double>(m + 1));
    std::vector<std::vector<double>> d(n + 1, std::vector<double>(m + 1));

    Statistic result(n, m, minEps, maxCount);

    // fill realValue
    for (int j = 0; j <= m; j++)
    {
        for (int i = 0; i <= n; i++)
        {
            result.realValue[i][j] = u(getX(i), getY(j));
        }
    }

    do
    {
        getDiscrepancy(d);
        if (count == 0)
        {
            h = d;
        } else 
        {
            double betta = util::scalarMul(ah, d) / util::scalarMul(ah, h);
            for (int j = 0; j <= m; j++)
            {
                for (int i = 0; i <= n; i++)
                {
                    h[i][j] = -d[i][j] + betta * h[i][j];
                }
            }
        }

        for (int j = 1; j < m; j++)
        {
            for (int i = 1; i < n; i++)
            {
                if (checkCoeficient(i, j))
                {
                    double res = 0.;
                    for (int num = 0; num < 5; num++)
                    {
                        int ni = i + dx[num];
                        int nj = j + dy[num];
                        if (checkCoeficient(ni, nj) || isBoard(ni, nj))
                        {
                            res += h[ni][nj] * coef[num];
                        }
                    }
                    ah[i][j] = res;
                }
            }
        }

        double alpha = -util::scalarMul(d, h) / util::scalarMul(ah, h);
        
        for (int j = 1; j < m; j++)
        {
            for (int i = 1; i < n; i++)
            {
                if (checkCoeficient(i, j))
                {
                    double new_v = v[i][j] + alpha * h[i][j];
                    eps = std::max(eps, std::fabs(new_v - v[i][j]));
                    v[i][j] = new_v;
                }
            }
        }
        count++;

    } while(eps >= minEps && count <= maxCount);

    result.solvedValue = v;
    return result;
}

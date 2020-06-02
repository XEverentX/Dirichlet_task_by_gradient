#include "statistic.hpp"

Statistic::Statistic(int n_n, int n_m, int n_minEps, int n_maxCount)
        : n(n_n), m(n_m), minEps(n_minEps), maxCount(n_maxCount),
          discrepancyNorm(0.), initialDiscrepancyNorm(0.),
          inaccuracy(0.), eps(0.), count(0.),
          maxDiscrepancyX(0.), maxDiscrepancyY(0.)
{
    realValue   = std::vector<std::vector<double>>(m + 1, std::vector<double>(n + 1));
    diffValue   = std::vector<std::vector<double>>(m + 1, std::vector<double>(n + 1));
    solvedValue = std::vector<std::vector<double>>(m + 1, std::vector<double>(n + 1));
}

auto Statistic::getReference() const -> std::string
{
    std::string result = "Для решения тестовой задачи использована сетка-основа\n\
        с числом разбиений по x n = «" + std::to_string(n) + "» и числом разбиений по y m = «" + std::to_string(m) + "»,\n\
        метод сопряженных градиентов,\n\
        критерии остановки по точности ε = «" + std::to_string(minEps) + "» и по числу итераций Nmax =«" + std::to_string(maxCount) + "»\n\
        На решение схемы (СЛАУ) затрачено итераций N =«" + std::to_string(count) + "» и достигнута точность итерационного метода ε(N)\n\
        = «" + std::to_string(eps) + "»\n\
        Схема (СЛАУ) решена с невязкой || R (N) || = «" + std::to_string(discrepancyNorm) + "»\n\
        для невязки СЛАУ использована норма «евклидова»;\n\
        Тестовая задача должна быть решена с погрешностью не более ε = 0.5⋅10 –6;\n\
        задача решена с погрешностью ε1 =«" + std::to_string(inaccuracy) + "»\n\
        Максимальное отклонение точного и численного решений наблюдается в узле \
        x=«" + std::to_string(maxDiscrepancyX) + "»; y=«" + std::to_string(maxDiscrepancyY) + "»\n\
        В качестве начального приближения использовано «нулевое начальное приближение»\n\
        Невязка СЛАУ на начальном приближении || R (0) || = «" + std::to_string(initialDiscrepancyNorm) + "»";

    return result;
}

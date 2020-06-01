#include "statistic.hpp"

std::string Statistic::getReference() const
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

#ifndef CHISQUARED_HPP
#define CHISQUARED_HPP

#include <vector>
#include <map>

#ifdef WIN32
#ifdef FEX_CNBCDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif

// Модуль принятия решений
// Хи-квадрат критерий

// Таблица квантилей распределения хи-квадрат для
// всех alpha для 9 степеней свободы в формате:
// "alpha" - "квантиль".
const std::map <double, double> table
{
    {0.01, 2.0879}, {0.025, 2.7004},    {0.05, 3.3251},     {0.1, 4.1682},      {0.2, 5.3801},
    {0.3, 6.3933},  {0.4, 7.3570},      {0.5, 8.3428},      {0.6, 9.4136},      {0.7, 10.6564},
    {0.8, 12.2421}, {0.9, 14.6837},     {0.95, 16.9190},    {0.975, 19.0228},   {0.99, 21.6660}
};

extern "C" DLLEXPORT
{
    // Проверка того, имеется ли введённое alpha в таблице
    // параметров и квантилей.
    bool IsAlpha(double alpha);

    // Хи-квадрат критерий для последовательности
    // p-value величин
    bool ChiSquareCheck(std::vector<double> pvalue, double alpha);
}

#endif // CHISQUARED_HPP


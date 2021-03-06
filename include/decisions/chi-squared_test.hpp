#ifndef CHISQUARED_TEST_HPP
#define CHISQUARED_TEST_HPP

#include <vector>
#include <map>

// Модуль принятия решений
// Таблица квантилей распределения хи-квадрат: все alpha,
// 9 степеней свободы.
std::map <double, double> table
{
    {0.01, 2.0879}, {0.025, 2.7004}, {0.05, 3.3251}, {0.1, 4.1682}, {0.2, 5.3801},
    {0.3, 6.3933}, {0.4, 7.3570}, {0.5, 8.3428}, {0.6, 9.4136}, {0.7, 10.6564},
    {0.8, 12.2421}, {0.9, 14.6837}, {0.95, 16.9190}, {0.975, 19.0228}, {0.99, 21.6660}
};

// Проверка того, имеется ли введённое alpha в таблице
// параметров и квантилей. Лень возиться с параметрами,
// пусть они проверяются в ядре, а сюда присылают годные
// alpha.
bool isAlpha(double &alpha);

// On-start testing
// Хи-квадрат критерий
// --------------------------
// Разбиваем массив pset на 10 непересекающихся интервалов и
// проверяем хи-квадрат критерием на true || false.
bool chiSquareCheck(std::vector <double> &pset, double &alpha);

#endif // CHISQUARED_TEST_HPP


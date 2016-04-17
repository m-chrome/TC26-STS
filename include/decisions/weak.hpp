#ifndef WEAK_HPP
#define WEAK_HPP

#include <vector>

// Модуль принятия решений
// Тест на "слабость"

// Для массива pset считает число pvalue, меньших alpha.
// Если это число больше 100*alpha, то вернуть 1 (fail),
// иначе вернуть 0 (check).
bool WeakCheck(std::vector <double> &pvalue, double &alpha);

#endif // WEAK_HPP


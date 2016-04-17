#ifndef WEAK_HPP
#define WEAK_HPP

#include <vector>

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
// Тест на "слабость"

// Для массива pset считает число pvalue, меньших alpha.
// Если это число больше 100*alpha, то вернуть 1 (fail),
// иначе вернуть 0 (check).

extern "C" DLLEXPORT
{
    bool WeakCheck(std::vector <double> &pvalue, double &alpha);
}

#endif // WEAK_HPP

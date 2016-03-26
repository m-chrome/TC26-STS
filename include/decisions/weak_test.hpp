#ifndef WEAK_TEST_HPP
#define WEAK_TEST_HPP

#include <vector>

using namespace std;

namespace decisions
{
    // On-start testing
    // Weak test
    // Для массива pset считает число pvalue, меньших alpha.
    // Если это число больше 100*alpha, то вернуть 1 (fail),
    // иначе вернуть 0 (check).
    bool pvalueCheck(vector <double> &pset, double &alpha);
}

#endif // WEAK_TEST_HPP


#ifndef WEAK_TEST_HPP
#define WEAK_TEST_HPP

#include <vector>

<<<<<<< HEAD
// On-start testing
// Weak test
// Для массива pset считает число pvalue, меньших alpha.
// Если это число больше 100*alpha, то вернуть 1 (fail),
// иначе вернуть 0 (check).
bool pvalueCheck(std::vector <double> &pset, double &alpha);
=======
using namespace std;

namespace decisions
{
    // On-start testing
    // Weak test
    // Для массива pset считает число pvalue, меньших alpha.
    // Если это число больше 100*alpha, то вернуть 1 (fail),
    // иначе вернуть 0 (check).
    bool weakCheck(vector <double> &pset, double &alpha);
}
>>>>>>> corepart

#endif // WEAK_TEST_HPP


#include "include/decisions/weak_test.hpp"
#include <vector>

bool pvalueCheck(std::vector <double> &pset, double &alpha)
{
    int weakpvalue = 0;
    for(std::size_t i=0; i < pset.size(); ++i)
        if (pset[i]<alpha)
            weakpvalue++;
    return weakpvalue <= 100*alpha;
}

#include "include/decisions/weak.hpp"

#include <vector>

bool WeakCheck(std::vector <double> &pvalue, double &alpha)
{
    int weakpvalue = 0;
    for(std::size_t i=0; i < pvalue.size(); ++i)
        if (pvalue[i]<alpha)
            weakpvalue++;
    return weakpvalue <= 100*alpha;
}

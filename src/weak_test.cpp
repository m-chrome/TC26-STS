#include "include/decisions/weak_test.hpp"
#include <vector>

using namespace std;
using namespace decisions;

bool pvalueCheck(vector <double> &pset, double &alpha)
{
    int weakpvalue = 0;
    for(size_t i=0; i < pset.size(); ++i)
        if (pset[i]<alpha)
            weakpvalue++;
    return weakpvalue <= 100*alpha;
}

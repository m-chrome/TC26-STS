#include "include/decisions/weak_test.hpp"
#include <vector>

<<<<<<< HEAD
bool pvalueCheck(std::vector <double> &pset, double &alpha)
=======
using namespace std;
using namespace decisions;

bool weakCheck(vector <double> &pset, double &alpha)
>>>>>>> corepart
{
    int weakpvalue = 0;
    for(std::size_t i=0; i < pset.size(); ++i)
        if (pset[i]<alpha)
            weakpvalue++;
    return weakpvalue <= 100*alpha;
}

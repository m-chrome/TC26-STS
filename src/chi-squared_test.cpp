#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include "include/decisions/chi-squared_test.hpp"

using namespace std;
using namespace decisions;

bool isAlpha(double &alpha)
{
    return table.find(alpha) != table.end();
}

bool chiSquareCheck(vector <double> &pset, double &alpha)
{
    sort(pset.begin(), pset.end());

    const int       NGroups         = 10;
    const double    pv_probability  = 0.1;
    int             pv_counter      = 0;
    int             nSize           = pset.size();
    double          uborder         = 0.1;
    double          chi_expr        = 0;
    double          chi_qntl        = (table.find(1-alpha))->second;

    for(int i=0; i < NGroups; ++i)
    {
        int pv_freaquency=0;
        while(pset[pv_counter] < uborder)
        {
            ++pv_counter;
            ++pv_freaquency;
        }
        chi_expr += pow(pv_freaquency-nSize*pv_probability, 2)/(nSize*pv_probability);
        uborder += 0.1;
    }
    return chi_expr <= chi_qntl;
}


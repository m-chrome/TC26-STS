#include "include/decisions/chisquared.hpp"

#include <vector>
#include <cmath>

bool IsAlpha(double alpha)
{
    return table.find(alpha) != table.end();
}

bool ChiSquareCheck(std::vector <double> &pvalue, double &alpha)
{
    const int       NGROUPS         = 10;
    const double    PV_PROBABILITY  = 0.1;
    int             pv_counter      = 0;
    int             nSize           = pvalue.size();
    double          uborder         = 0.1;
    double          chi_expr        = 0;
    double          chi_qntl        = (table.find(1-alpha))->second;

    for(int i=0; i < NGROUPS; ++i)
    {
        int pv_freaquency=0;
        while(pvalue[pv_counter] < uborder)
        {
            ++pv_counter;
            ++pv_freaquency;
        }
        chi_expr += std::pow(pv_freaquency-nSize*PV_PROBABILITY, 2)/(nSize*PV_PROBABILITY);
        uborder += 0.1;
    }
    return chi_expr <= chi_qntl;
}


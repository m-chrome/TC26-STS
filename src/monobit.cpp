#include "../include/statistical_tests/monobit.hpp"
#include "../include/tc26/cephes.hpp"
#include "../include/tc26/utility.hpp"

#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>

double monobittest(std::ifstream &input, int argc, char **)
{
    assert(argc==0);
    int length=nvalue, sum = 0,size=0;
    char bit;
    input >> bit;
    if(length)
    {
        for(int i=0;i<length;++i)
        {
            if(input)
            {
                (bit!='0')? ++sum:--sum;
                ++size;
                input >> bit;
            }
        }
    }
    else
    {
        while(input)
        {
            (bit!='0')? ++sum:--sum;
            ++size;
            input >> bit;
        }
        --size;
    }
    return cephes_erfc(abs(sum)/sqrt(2*size));
}


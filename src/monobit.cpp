#include "include/statistical_tests/monobit.hpp"
#include "include/tc26/cephes.hpp"

#include <cmath>
#include <cassert>
#include <cstring>

double monobittest(std::ifstream &input, int argc, char *argv[])
{
    assert(argc==1);
    int length=atoi(argv[0]), sum = 0,size=0;
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


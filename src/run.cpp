#include "run.hpp"
double runtest(std::ifstream& input, int argc, char **argv)
{
    assert(argc==1);
    int length=atoi(argv[0]),size=0;
    char prev,cur;
    long mu=0;
    long double sum=0;
    input >> prev;
    ++size;
    if(length)
    {
        for(int i=1;i<length;++i)
        {
            if(input)
            {
                input >> cur;
                if(cur==prev) ++mu;
                prev=cur;
                ++size;
            }
        }
    }
    else
    {
        while(input)
        {
            input >> cur;
            if(cur==prev) ++mu;
            prev=cur;
            ++size;
        }
    }
    sum=(mu-(size-1)/2)/(std::sqrt(size-2+(3*size-5)/2));
    return erfc(std::abs(sum)/std::sqrt(2));
}

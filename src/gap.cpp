#include "../include/statistical_tests/gap.hpp"
#include "../include/tc26/cephes.hpp"
#include "../include/tc26/utility.hpp"

#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

double p(int A, int B, int m){
    return (double)(B-A +1)/(1<<m);
}

double pt(double p, int t){
    return pow((1-p),t);
}

double pi(double p, int i){
    return p*pow((1-p),i);
}


size_t M(std::vector<size_t> &vec_vi, int t){
    size_t result;
    std::for_each(vec_vi.begin(), vec_vi.end(), [&result](size_t v){
        result += v;
    } );
    return result;
}


double Sn(std::vector<size_t> &vec_vi,size_t t, int A, int B, int m){
    double result=0;
    for(size_t i = 0; i < t; i++){
        double buf = M(vec_vi,t) * pi(p(A,B,m),i);
        result += (((double)vec_vi[i] - buf)/buf);
    }
    return result;
}

double gaptest(std::ifstream &input, int argc, char** argv)
{    
    assert(argc==0);

    //{"gaptest",
    //{4,"
    //[a1-1] is maximum length of the interval;
    //[a2] is a length of a tuple;
    //[a3] is a left border of the testing section;
    //[a4] is a right border of the testing section"}},
    size_t t = std::stoul(std::string (argv[0]));
    size_t m = std::stoul(std::string (argv[1]));
    size_t A = std::stoul(std::string (argv[2]));
    size_t B = std::stoul(std::string (argv[3]));
    size_t m2 = ( 1 << m) -1;
    int length = nvalue;
    size_t N = length /m;
    char bit;
    std::vector<size_t> vec_vals;
    std::vector<size_t> vec_vi(t);
    std::for_each(vec_vi.begin(),vec_vi.end(),[](size_t &p_){p_=0;});

    for (size_t i = 0;i <N; i++){
        std::string buf;
        for(size_t k=0; k < m; k++ ){
            buf += input.get();
            if (!input) {break;}
        }
        if (!input) {break;}
        vec_vals.push_back(std::stoul(buf));
    }
    size_t count =0;
    for(size_t i:vec_vals){
        if(  !(A<i && i <B ) ){
            count += 1;
        }else{
            if (count != 0){
                if (count <t ){
                    vec_vi[count]++;
                }else{
                    vec_vi[t]++;
                }
                count =0;
            }
        }
    }
    double pvalue;
    pvalue = cephes_igamc(t-1,Sn(vec_vi,t,A,B,m));
   return pvalue;
}

#include "include/statistical_tests/randomwalk.hpp"
#include "include/tc26/cephes.hpp"
#include <cstring>
#include <vector>
#include <cmath>
#include <iostream>

double randomwalktest(std::ifstream &input, int argc, char* argv[]){
    int length=atoi(argv[0]), sum = 0,x;
int state=atoi(argv[1]);
    if(state==0){
      std::cerr<<"wrong state x argument in random walk";
      return -1;
    }
    if(argc<2){
        std::cerr<<"less arguments in random walk";
        return -1;
    }
    if(state>0)
        state=state+(length/2)+1;
    else
        state=state+(length/2);
    int max=0, max1=0,J=0;
    char bit;
    std::vector<int> s;
    s[0]=0;
    input >> bit;
    if(length)
    {
        for(int i=0;i<length;++i)
        {
            if(input)
            {
                if (bit!='0')
                    ++sum;
                else
                    --sum;
                s[i+i]=sum;
                input >> bit;
            }
        }
      s[length+1]=0;
    }
    else
    {
        int i=1;
        while(input)
        {
            if (bit!='0')
                ++sum;
            else
                --sum;
            s[i]=sum;
            input >> bit;
            i++;
        }
      s[i+1]=0;
    }

    for(int i=1;i<length;i++){
        if(s[i])
            max1++;
        else{
            J++;
            if(max<max1)
                max=max1;
            max1=0;
        }
    }
    vector<vector<int>> M(length);
    for ( int i = 0 ; i < length ; i++ )
       M[i].resize(max);
    vector<int> cy(J);
    for(int x1=0;x1<length;x1++){
       int x2;
       if(x1<(length/2))
           x2=x1-(length/2);
       else
           x2=x1-(length/2)+1;
       int j=0;
       for(int o=0;o<J;o++)
           cy[o]=0;
       for(int l=1;l<length;l++){
           if(s[l]==0)
               ++j;
           else{
            if(s[l]==x2)
              cy[j]++;
           }
       }
       for(int k=0;k<J;k++){
           int c=cy[k];
           M[x1][c]++;
       }
    }
    vector<vector<double>> M1(length);
    for ( int i = 0 ; i < length ; i++ )
       M1[i].resize(max);
    vector<double> X(length);
    for ( int i = 0 ; i < length ; i++ )
       X[i]=0;
    for(int x=0;x<length;x++){
        int x1;
        if(x<(length/2))
            x1=(length/2)-x;
        else
            x1=x-(length/2)+1;
        for(int k=0;k<max;k++){
            if(!k){
                double a=1/(2.0*x1);
                double b =1-a;
                double c=J*b;
                double d=(double)(M[x][k]-c);
                double v0=pow(d,2);
                M1[x][k]=v0/c;
            }
            else{
                double a=4.0*x1*x1;
                double b=1/a;
                double c=1/(2.0*x1);
                double d=1-c;
                double e=pow(d,k-1);
                double f=J*b*e;
                double g=M[x][k]-f;
                double g2=pow(g,2);
                M1[x][k]=g2/f;
            }
        }
    }
    for(int i=0;i<length;i++){
        for(int k=0;k<max;k++)
            X[i]+=M1[i][k];
    }

    for(int i=0;i<length;i++){
        double x=cephes_igamc(5/2,X[i]/2);
        X[i]=x;
    }
return X[state];
}

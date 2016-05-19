#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef WIN32
#define SLASH "\\"
#else
#define SLASH "/"
#endif

#include "include/tc26/core.hpp"

#include <map>
#include <string>

const int nvalue=1000000;

template<typename ForwardIterator>
auto direct_Search(ForwardIterator begin,ForwardIterator end,std::string key)
{

    for(ForwardIterator i=begin;i!=end;++i)
        if(i->m_testName==key)
            return i;
    return end;
};

void ClearStr(char* s,int n=255);

bool UseConfigFile(char* name, Core& core, bool& userOutputFile);

#endif // UTILITY_HPP


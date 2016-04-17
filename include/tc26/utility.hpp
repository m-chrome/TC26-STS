#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef WIN32
#define SLASH "\\"
#else
#define SLASH "/"
#endif

#include <map>
#include <string>

struct testInfo
{
    int t_argc;
    std::string description;
};

const std::map<std::string,testInfo> utilityTable
{
    {"monobittest",{0,"no arguments"}},
    {"runtest",{0,"no arguments"}},
    {"ovrlpchisquaretest",{1,"[a1] is a length of a tuple"}},
    {"gaptest",{4,"[a1-1] is maximum length of the interval; [a2] is a length of a tuple; [a3] is a left border of the testing section; [a4] is a right border of the testing section"}},
    {"maurertest",{0,"no arguments"}},
    {"randomwalktest",{0,"no arguments"}}
};

template<typename ForwardIterator>
auto direct_Search(ForwardIterator begin,ForwardIterator end,std::string key)
{

    for(ForwardIterator i=begin;i!=end;++i)
        if(i->m_testName==key)
            return i;
    return end+1;
};

#endif // UTILITY_HPP


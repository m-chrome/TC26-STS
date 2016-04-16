#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <map>
#include <string>

struct testInfo
{
    int t_argc;
    std::string description;
};

std::map<std::string,testInfo> utilityTable{
    {"monobittest",{0,"no arguments"}},{"runtest",{0,"no arguments"}},{"ovrlpchisquaretest",{1,"[a1] is a length of a tuple"}},
    {"gaptest",{4,"[a1-1] is maximum length of the interval; [a2] is a length of a tuple; [a3] is a left border of the testing section; [a4] is a right border of the testing section"}},
    {"maurertest",{0,"no arguments"}}, {"randomwalktest",{0,"no arguments"}}
};
#endif // UTILITY_HPP

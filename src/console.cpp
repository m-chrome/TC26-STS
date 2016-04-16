#include "include/ui/console.hpp"
#include "include/tc26/utility.hpp"

#include <iostream>

void Console::help(Core core)
{
    std::cout << "tc26-STS [--testname [args]] [-i directory] [-o file]\n\n";
    std::cout << "\t--testname: names of tests with its arguments\n";
    std::cout << "\t-i: directory is a path to directory with input files\n";
    std::cout << "\t-o: output file for containing results\n\n";
    std::cout << "Availible tests:\n";
    for(auto& el: core.m_allTests)
    {
        std::cout << "--" << el.m_testName << '\t';
        for(int i=1;i<=utilityTable.find(el.m_testName)->second.t_argc;++i)
            std::cout << "arg" << i << ' ';
        std::cout << '\t' << utilityTable.find(el.m_testName)->second.description << '\n';
    }
}

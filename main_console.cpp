#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"

#include <cstring>
#include <iostream>

#include <QCoreApplication>
#include <qglobal.h>

int main(int argc, char *argv[])
{
    Core core;
    if(argc==1)
    {
        std::cerr << "Try tc26-STS --help";
        return 0;
    }

    if(!strcmp(argv[1],"--help"))
    {
        Console::Help(core);
        return 0;
    }
    if(core.m_isAllChecked == 1)
    {
        Console::OutputResults(core);
    }
    return 0;
}


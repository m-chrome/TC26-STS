#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"

#include <cstring>

int main(int argc, char *argv[])
{
    Core core;
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


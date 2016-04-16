#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"

#include <cstring>

#include <QCoreApplication>
#include <qglobal.h>

int main(int argc, char *argv[])
{
    Core core;
    if(!strcmp(argv[1],"--help"))
    {
        Console::help(core);
        return 0;
    }
    return 0;
}


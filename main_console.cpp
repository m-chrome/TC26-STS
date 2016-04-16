#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"
#include "include/tc26/utility.hpp"

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
        Error:Console::Help(core);
        return 0;
    }
    if(!strcmp(argv[1],"-p")) goto Error;
    if(atof(argv[2])>=1||atof(argv[2])<=0) goto Error;
    //alpha = atof(argv[2])
    for(int i=3;i<argc;++i)
    {
        if(argv[i][0]=='-')
        {
            if(argv[i][1]=='-')
            {
                char temp[30];
                strcpy(&argv[i][2],temp);
                if(utilityTable.find(temp)==utilityTable.end()) goto Error;
                core.m_useTests.emplace_back(*direct_Search(core.m_allTests.begin(),core.m_allTests.end(),std::string(temp)));
                for(int j=0;j<utilityTable.find(temp)->second.t_argc;++j)
                {
                    //проверить, правильное ли количество параметров подается после теста
                    (core.m_useTests.end()-1)->m_testParameters.second[j]=argv[++i];
                }
                (core.m_useTests.end()-1)->m_testParameters.first=utilityTable.find(temp)->second.t_argc;
            }
            //дописать обработку не для тестов с их параметрами(параметры для тестов обрабатываются вместе с именами тестов)
        }
        goto Error;
    }
    if(core.m_isAllChecked == 1)
    {
        Console::OutputResults(core);
    }
    return 0;
}


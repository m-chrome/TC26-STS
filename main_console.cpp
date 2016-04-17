#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"
#include "include/tc26/utility.hpp"
#include "include/tc26/types.hpp"
#include "include/decisions/chisquared.hpp"

#include <cstring>
#include <iostream>

#include <QCoreApplication>
#include <qglobal.h>

int main(int argc, char *argv[])
{
    const char* interpreter="1234567890.e+-";
    bool userOutputFile =false;
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
    if(std::strspn(argv[2],interpreter)!=strlen(argv[2])||!IsAlpha(atof(argv[2]))) goto Error;
    core.setAlphaParameter(atof(argv[2]));
    for(int i=3;i<argc;++i)
    {
        if(argv[i][0]=='-')
        {
            if(argv[i][1]=='-')
            {
                //Модифицировать так, чтобы убрать allTests и useTests из public
                char temp[30];
                strcpy(&argv[i][2],temp);
                if(utilityTable.find(temp)==utilityTable.end()) goto Error;
                core.m_useTests.emplace_back(*direct_Search(core.m_allTests.begin(),core.m_allTests.end(),std::string(temp)));
                for(int j=0;j<utilityTable.find(temp)->second.t_argc;++j)
                {
                    if(argv[++i][0]=='-'||std::strspn(argv[i],interpreter)!=strlen(argv[i])) goto Error;
                    (core.m_useTests.end()-1)->m_testParameters.second[j]=argv[i];
                }
                (core.m_useTests.end()-1)->m_testParameters.first=utilityTable.find(temp)->second.t_argc;
                continue;
            }
            if(argv[i][1]=='i')
            {
                if(argv[i][2]=='f')
                {
                    if(!Console::AddFileToFileMap(core,argv[++i])) goto Error;
                    continue;
                }
                if(argv[i][2]=='d')
                {
                    std::size_t filesCount=Console::AddDirectoryToFileMap(core,argv[++i]);
                    if(!filesCount) goto Error;
                    std::cout << filesCount << " was added successfully from " << argv[i] << '\n';
                    continue;
                }
            }
            if(argv[i][1]=='o')
            {
                if(userOutputFile)
                {
                    std::cerr << "Multiple definition of output file.\n";
                    goto Error;
                }
                userOutputFile=true;
                if(!Console::ChooseOutputFile(core,argv[++i])) goto Error;
                continue;
            }
            std::cerr << "Invalid input parameters.\n";
            goto Error;
        }
        std::cerr << "Invalid input parameters.\n";
        goto Error;
    }
    if(!userOutputFile) Console::ChooseOutputFile(core,"TestingResults.txt");
    if(core.getTestsResult() == 1)
    {
        Console::OutputResults(core);
    }
    return 0;
}


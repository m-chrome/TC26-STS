#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"
#include "include/tc26/utility.hpp"

#include <cstring>
#include <iostream>

#include <QCoreApplication>
#include <qglobal.h>

int main(int argc, char *argv[])
{
    const char* interpreter="1234567890.e+-";
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
    if(std::strspn(argv[2],interpreter)!=strlen(argv[2])||atof(argv[2])>=1||atof(argv[2])<=0) goto Error;
    core.setAlphaParameter(atof(argv[2]));
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
                    if(argv[++i][0]=='-'||std::strspn(argv[i],interpreter)!=strlen(argv[i])) goto Error;
                    (core.m_useTests.end()-1)->m_testParameters.second[j]=argv[i];
                }
                (core.m_useTests.end()-1)->m_testParameters.first=utilityTable.find(temp)->second.t_argc;
                continue;
            }
            if(argv[i][1]=='i')
                if(argv[i][2]=='f')
                {
                    std::fstream* temp = new std::fstream(argv[++i],std::ios_base::in);
                    if(!temp->good())
                    {
                        std::cerr << "Failed to open input file " << argv[i] << ".\n\n";
                        goto Error;
                    }
                    //TODO
                }
            //TODO
        }
        goto Error;
    }
    if(core.getTestsResult() == 1)
    {
        Console::OutputResults(core);
    }
    return 0;
}


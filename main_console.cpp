#include "include/tc26/core.hpp"
#include "include/ui/console.hpp"
#include "include/tc26/utility.hpp"
#include "include/tc26/types.hpp"
#include "include/decisions/chisquared.hpp"

#include <cstring>
#include <string>
#include <iostream>

#include <QCoreApplication>
#include <qglobal.h>

int main(int argc, char *argv[])
{
    bool userOutputFile =false;
    Core core("uTable.cfg");
    if(argc==1)
    {
        std::cerr << "Try tc26-STS --help\n";
        return 0;
    }
    if(!strcmp(argv[1],"--help"))
    {
Error:Console::Help(core);
        return 0;
    }
    if(!strcmp(argv[1],"-c"))
    {
        if(!UseConfigFile(argv[2],core,userOutputFile)) goto Error;
    }
    else
    {
        if(strcmp(argv[1],"-p")) goto Error;
        if(std::strspn(argv[2],Console::interpreter)!=strlen(argv[2])||!IsAlpha(atof(argv[2]))) goto Error;
        core.setAlphaParameter(atof(argv[2]));
        for(int i=3;i<argc;++i)
        {
            if(argv[i][0]=='-')
            {
                if(argv[i][1]=='-')
                {
                    char temp[30];
                    strcpy(temp,argv[i]+2);
                    if(core.utilityTable.find(temp)==core.utilityTable.end()||direct_Search(core.getAllTests().begin(),core.getAllTests().end(),std::string(temp))==core.getAllTests().end()) goto Error;
                    core.getUseTests().emplace_back(*direct_Search(core.getAllTests().begin(),core.getAllTests().end(),std::string(temp)));
                    for(int j=0;j<core.utilityTable.find(temp)->second.t_argc;++j)
                    {
                        if(argv[++i][0]=='-'||std::strspn(argv[i],Console::interpreter)!=strlen(argv[i])) goto Error;
                        (core.getUseTests().end()-1)->m_testParameters.second[j]=argv[i];
                    }
                    (core.getUseTests().end()-1)->m_testParameters.first=core.utilityTable.find(temp)->second.t_argc;
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
                        if(!filesCount)
                        {
                            std::cerr << "No input files were found in " << argv[i] << ".\n";
                            goto Error;
                        }
                        std::cout << filesCount << " file(s) was added successfully from " << argv[i] << '\n';
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
    }
    if(!Console::GetInputFilesCount(core))
    {
        std::cerr << "No input files.\n";
        goto Error;
    }
    if(!userOutputFile) Console::ChooseOutputFile(core,"TestingResults.txt");
    core.Logic();
    if(core.getTestsResult() == 1)
    {
        Console::OutputResults(core);
    }
    return 0;
}


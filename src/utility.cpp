#include "include/ui/console.hpp"
#include "include/decisions/chisquared.hpp"
#include "include/tc26/utility.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>

bool UseConfigFile(char* name, Core& core, bool &userOutputFile)
{
    std::ifstream file(name);
    if(!file.good())
    {
        std::cerr << "Failed to open config file.\n";
        return false;
    }
    char sym, temp[255];
    while(file)
    {
        file.get(sym);
        if(sym=='#')
        {
            file.getline(temp,255);
            continue;
        }
        file.unget();
        file.getline(temp,255,'=');
        if(!strcmp(temp,"Alpha"))
        {
            file.getline(temp,255);
            if(std::strspn(temp,Console::interpreter)!=strlen(temp)||!IsAlpha(atof(temp)))
            {
                std::cerr << "Bad alpha value.\n";
                return false;
            }
            core.setAlphaParameter(atof(temp));
            continue;
        }
        if(!strcmp(temp,"Test"))
        {
            char test[30];
            file.getline(test,30,' ');
            std::strcat(test,"test");
            if(utilityTable.find(test)==utilityTable.end()||direct_Search(core.getAllTests().begin(),core.getAllTests().end(),std::string(test))==core.getAllTests().end()) return false;
            core.getUseTests().emplace_back(*direct_Search(core.getAllTests().begin(),core.getAllTests().end(),std::string(test)));
            file.getline(temp,255);
            std::istringstream arguments(temp);
            for(int j=0;j<utilityTable.find(test)->second.t_argc;++j)
            {
                std::size_t arg;
                char a[30];
                if(!arguments)
                {
                    std::cerr << "Not enough parameters in " << test;
                    return false;
                }
                arguments >> arg;
                snprintf(a,strlen(a),"%zu",arg);
                (core.getUseTests().end()-1)->m_testParameters.second[j]=a;
            }
            (core.getUseTests().end()-1)->m_testParameters.first=utilityTable.find(temp)->second.t_argc;
            continue;
        }
        if(!strcmp(temp,"InputFile"))
        {
            file.getline(temp,255);
            if(!Console::AddFileToFileMap(core,temp)) return false;
            continue;
        }
        if(!strcmp(temp,"InputDirectory"))
        {
            file.getline(temp,255);
            std::size_t filesCount=Console::AddDirectoryToFileMap(core,temp);
            if(!filesCount) return false;
            std::cout << filesCount << " file(s) was added successfully from " << temp << '\n';
            continue;
        }
        if(!strcmp(temp,"OutputFile"))
        {
            file.getline(temp,255);
            if(userOutputFile)
            {
                std::cerr << "Multiple definition of output file.\n";
                return false;
            }
            userOutputFile=true;
            if(!Console::ChooseOutputFile(core,temp)) return false;
            continue;
        }
        std::cerr << "The content of config file is incorrect.\n";
        return false;
    }
    return true;
}

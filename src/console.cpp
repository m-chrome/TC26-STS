#include "include/ui/console.hpp"
#include "include/tc26/utility.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <QDir>
#include <QString>
#include <QStringList>

void Console::Help(const Core& core)
{
    std::cout << "TC26-STS [-p alpha] [--testname [args]] [-id directory] [-if file] [-o file]] [-c file]\n\n";
    std::cout << "\t-c: config file(use INSTEAD OF other arguments)\n";
    std::cout << "\t-p: alpha parameter\n";
    std::cout << "\t--testname: names of tests with its arguments\n";
    std::cout << "\t-id: directory is a path to directory with input files\n";
    std::cout << "\t-if: add an input file\n";
    std::cout << "\t-o: output file for containing results\n\n";
    std::cout << "Availible tests:\n";
    for(auto& el: core.m_allTests)
    {
        std::cout << "--" << el.m_testName << '\t';
        for(int i=1;i<=core.utilityTable.find(el.m_testName)->second.t_argc;++i)
            std::cout << "arg" << i << ' ';
        std::cout << '\t' << core.utilityTable.find(el.m_testName)->second.description << '\n';
    }

    std::cout << "\nAvailible decision modules:\n";
    for(auto &dec: core.m_decisions)
    {
        std::cout << '\t' << dec.m_decName << '\n';
    }
}

void Console::OutputResults(Core& core)
{
    std::cout << "Results of testing:\n\n";
    core.m_resultFile << "Results of testing:\n\n";
    for(auto &file: core.m_openFiles)
    {
        std::cout << (file.second).fileName << '\n';
        core.m_resultFile << (file.second).fileName << '\n';
        std::string resultMessage;
        for(auto &test: file.second.testResults)
        {
            if(test.second)
                resultMessage = "Passed";
            else
                resultMessage = "Not passed";
            std::cout << "\t- " << test.first << "\t\t-- " << resultMessage << std::endl;
            core.m_resultFile<< "\t- " << test.first << "\t\t-- " << resultMessage << std::endl;
        }
    }
}

bool Console::AddFileToFileMap(Core &core, const char* name)
{
    std::fstream* temp = new std::fstream(name,std::ios_base::in);
    if(!temp->good())
    {
        std::cerr << "Failed to open input file " << name << ".\n\n";
        return false;
    }
    core.m_openFiles.emplace(temp,tc26::FileData(std::string(name)));
    return true;
}

int Console::AddDirectoryToFileMap(Core& core, const char* name)
{
    QDir dir((QString)(name));
    QStringList filters;
    filters << "*.txt" << "*.TXT";
    QStringList files=dir.entryList(filters);
    const std::size_t start = files.count();
    std::size_t bad=0;
    for(auto& file: files)
        if(!AddFileToFileMap(core,QString(name).append(SLASH).append(file).toStdString().c_str())) ++bad;
    return start-bad;
}

bool Console::ChooseOutputFile(Core& core,const char* name)
{
    core.m_resultFile.open(name,std::ios_base::out);
    if(!core.m_resultFile.good())
    {
        std::cerr << "Failed to open/create output file " << name << ".\n\n";
        return false;
    }
    return true;
}

std::size_t Console::GetInputFilesCount(const Core& core)
{
    return core.m_openFiles.size();
}

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
    std::cout << "TC26-STS -p alpha [--testname [args]] [-id directory] [-if file] [-o file]\n\n";
    std::cout << "\t-p: alpha parameter\n";
    std::cout << "\t--testname: names of tests with its arguments\n";
    std::cout << "\t-id: directory is a path to directory with input files\n";
    std::cout << "\t-if: add an input file\n";
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

void Console::OutputResults(Core& core)
{
    std::cout << "Results of testing:\n\n";
    core.m_resultFile << "Results of testing:\n\n";
    for(auto &file: core.m_openFiles)
    {
        std::string resultMessage;
        if (file.second.testResult)
            resultMessage = "Passed";
        else
            resultMessage = "Not passed";
        std::cout << (file.second).fileName << '\t' << resultMessage << std::endl;
        core.m_resultFile << (file.second).fileName << '\t' << resultMessage << std::endl;
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
    core.m_openFiles.emplace(temp,tc26::FileData(std::string(name),false));
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
        if(!AddFileToFileMap(core,file.toStdString().c_str())) ++bad;
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

#include "include/tc26/core.hpp"

#include <iostream>

static class Console
{
public:
    static void Help(const Core &core);
    static void OutputResults(Core &core);
    static bool AddFileToFileMap(Core &core, const char *name);
    static int AddDirectoryToFileMap(Core& core,const char* name);
    static bool ChooseOutputFile(Core& core,const char* name);
    static std::size_t GetInputFilesCount(const Core& core);
    static constexpr char* interpreter=(char *)"1234567890.e+-";
} Console;

#ifndef RANDOMWALK_HPP
#define RANDOMWALK_HPP

#include <fstream>

#ifdef WIN32
#ifdef FEX_CNBCDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif


extern "C" DLLEXPORT
{
    double randomwalktest( std::ifstream &input, int argc, char* argv[]);
}

#endif

#ifndef TESTMONOBIT_HPP
#define TESTMONOBIT_HPP

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
    double monobittest(std::ifstream &input, int argc, char **);
}

#endif // TESTMONOBIT_HPP

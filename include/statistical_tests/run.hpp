#ifndef RUN
#define RUN

#include <fstream>
#include <cassert>
#include <cstring>
#include <cmath>
#include <iostream>

#ifdef WIN32
#ifdef FEX_CNBCDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT double runtest(std::ifstream &input, int argc, char **argv);

#endif // RUN


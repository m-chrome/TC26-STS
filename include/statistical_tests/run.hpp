#ifndef RUN
#define RUN

#include <fstream>

#if defined(_MSC_VER) ||    \
    defined(__WIN32) ||     \
    defined(__WIN32__) ||   \
    defined(_WIN32) ||      \
    defined(WIN32) ||       \
    defined(__WINNT) ||     \
    defined(__WINNT__) ||   \
    defined(__WINNT)
#ifdef FEX_CNBCDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT double runtest(std::ifstream &input, int argc, char **);

#endif // RUN


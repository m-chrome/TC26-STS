#ifndef CORE_HPP
#define CORE_HPP

#include <fstream>
#include <vector>
#include <include/tc26/types.hpp>

class Core
{
public:
    //TODO
    /*--нужно как-то инициализировать core...после считывания с конфига.*/
    explicit Core();
    ~Core();


private:
    void logic();

    tc26::VecTests tests_;
    tc26::VecDecisions decisions_;
    tc26::VecStreams openFiles_;
};

#endif // CORE_HPP

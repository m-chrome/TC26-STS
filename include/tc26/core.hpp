#ifndef CORE_HPP
#define CORE_HPP

#include <include/tc26/types.hpp>

class Core
{
public:
    friend class Console;
    //TODO
    /*--нужно как-то инициализировать core...после считывания с конфига.*/
    explicit Core();
    ~Core();

private:
    tc26::StreamsCheck_t    m_openFiles;
    tc26::UsedTests_t       m_tests;
    tc26::UsedTests_t       m_allTests;
    tc26::UsedDecisions_t   m_decisions;
    tc26::ResultTable_t     m_pvalues;

    void Logic();
    void Parsing();
};

#endif // CORE_HPP

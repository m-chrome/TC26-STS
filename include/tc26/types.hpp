#ifndef TYPES
#define TYPES
/* Псевдонимы типов, с которыми можно будет работать. */

#include <iostream>
#include <vector>
#include <string>

namespace tc26 {
    //указатель на функцию в библиотеке тестов
    typedef double (*Test)(std::fstream&,int, char** );

    //указатель на функцию в библиотеке модуля принятия решений. (возможно нужно переделать(?))
    typedef bool (*Deсision)(std::vector<double> ,double);

    //тесты : указатель на функцию + параметры argc argv
    typedef std::vector< std::pair<Deсision, std::pair<int, char**> > > Tests;

    //модуль принятия решений: указатель на функцию + параметры.
    typedef std::vector< std::pair<Deсision, std::pair<int, char**> > > Decisions;

/*Я полагаю что со следующими псевдонимами будет удобнее работать:
*/

    class TestClass
    {
    public:
        Test func;
        std::pair<int, char**> testParameters;
        std::string name;// название теста
    };

    //аналог Tests
    typedef std::vector< TestClass> VecTests;


    class DecisionClass
    {
    public:
        Deсision func;
        double alfa;
        std::pair<int, char**> decisionParameters;
        std::string name;
    };

    //аналог Decisions
    typedef std::vector<DecisionClass> VecDecisions;

    typedef std::vector<std::fstream> VecStreams;
}
#endif // TYPES


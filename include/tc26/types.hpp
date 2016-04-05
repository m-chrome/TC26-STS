#ifndef TYPES
#define TYPES
/* Псевдонимы типов, с которыми можно будет работать. */

#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace tc26
{
    // Для работы с потоками и результатами их тестирования
    typedef std::multimap<std::fstream, bool> StreamsCheck_t;

    // Типы для тестов
    // Указатель на функцию теста
    typedef double (*TestFunc_t)(const std::fstream&, int, char** );

    // Объект определённого теста
    class TestObj
    {
    public:
        TestFunc_t              m_func;
        std::pair<int, char**>  m_testParameters;
        std::string             m_testName;
    };

    // Вектор всех выбранных пользователем тестов
    typedef std::vector<TestObj> UsedTests_t;

    // Типы для модуля принятия решения (МПР)
    // Указатель на функцию в МПР
    typedef bool (*DeсisionFunc_t)(std::vector<double> ,double);

    // Объект определённого теста из МПР
    class DecisionObj
    {
    public:
        DeсisionFunc_t          m_func;
        double                  m_alfa;
        std::pair<int, char**>  m_decParameters;
        std::string             m_decName;
    };

    // Вектор всех выбранных пользователем тестов МПР
    typedef std::vector<DecisionClass> UsedDecisions_t;
}
#endif // TYPES


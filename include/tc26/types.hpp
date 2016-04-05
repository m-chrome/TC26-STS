#ifndef TYPES
#define TYPES
/* Псевдонимы типов, с которыми можно будет работать. */

#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

namespace tc26
{
    // Для работы с потоками и результатами их тестирования
    typedef std::multimap<std::fstream, bool> StreamsCheck_t;

    // Табличка для хранения полученных pvalue от всех тестов
    typedef std::vector<std::set<double>> ResultTable_t;

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
    typedef bool (*DeсisionFunc_t)(std::set<double>, double);

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
    typedef std::vector<DecisionObj> UsedDecisions_t;
}
#endif // TYPES


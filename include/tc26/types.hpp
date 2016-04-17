#ifndef TYPES
#define TYPES

/* Псевдонимы типов, с которыми можно будет работать. */

#include <fstream>
#include <string>
#include <vector>
#include <map>

namespace tc26
{
    // Данные для файла
    struct FileData
    {
        std::string fileName;
        bool testResult;
    };

    // Для работы с потоками и результатами их тестирования
    typedef std::map<std::fstream*, FileData> StreamsCheck_t;

    // Табличка для хранения полученных pvalue от всех тестов
    typedef std::vector<std::vector<double>> ResultTable_t;


    // Типы для тестов
    // Указатель на функцию теста
    typedef double (*TestFunc_t)(const std::fstream&, int, char** );

    // Объект определённого теста
    class TestObj
    {
    public:
        TestObj(TestFunc_t f,std::pair<int, char**> arg,std::string name):
            m_func(f),
            m_testParameters(arg),
            m_testName(name){}
        TestFunc_t              m_func;
        std::pair<int, char**>  m_testParameters;
        std::string             m_testName;
    };

    // Вектор всех выбранных пользователем тестов
    typedef std::vector<TestObj> Tests_t;

    // Типы для модуля принятия решения (МПР)
    // Указатель на функцию в МПР
    typedef bool (*DeсisionFunc_t)(std::vector<double>, double);

    // Объект определённого теста из МПР
    class DecisionObj
    {
    public:
        DecisionObj(DeсisionFunc_t f, std::string name):
            m_func(f),
            m_decName(name) {}

        DeсisionFunc_t          m_func;
        std::string             m_decName;
    };

    // Вектор всех выбранных пользователем тестов МПР
    typedef std::vector<DecisionObj> Decisions_t;
}
#endif // TYPES

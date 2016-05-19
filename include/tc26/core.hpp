#ifndef CORE_HPP
#define CORE_HPP

#include <include/tc26/types.hpp>

#include <fstream>

#include <QString>

struct testInfo
{
    int t_argc;
    std::string description;
};

class Core
{
public:
    Core(const char* path);
    ~Core();

    // Внешние методы
    void setAlphaParameter(const double &alpha);
    bool getTestsResult() const;
    void Logic();
    tc26::Tests_t& getUseTests();
    tc26::Tests_t& getAllTests();

    std::map<std::string,testInfo> utilityTable;

    friend class Console;

private:
    // Нужные файлы (файлы для тестирования
    // + выходной файл с результатами)
    tc26::StreamsCheck_t    m_openFiles;
    std::fstream            m_resultFile;
    std::fstream            m_pvalueLog;

    // Тесты
    tc26::Tests_t       m_useTests;
    tc26::Tests_t       m_allTests;

    // Модуль принятия решений
    tc26::Decisions_t   m_decisions;

    // Таблица с pvalue
    tc26::ResultTable_t     m_pvalues;

    // Методы
    void ParsingTests(QString dest);
    void ParsingDecisions(QString dest);
    bool CreateUtilityTable(const char* path);

    // Нужные переменные
    bool                    m_isAllFileChecked;
    double                  m_alphaParameter;
};

#endif // CORE_HPP

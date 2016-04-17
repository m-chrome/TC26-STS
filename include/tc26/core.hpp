#ifndef CORE_HPP
#define CORE_HPP

#include <include/tc26/types.hpp>

#include <fstream>

#include <QString>

class Core
{
public:
    Core();
    ~Core();

    // Тесты
    tc26::Tests_t       m_useTests;
    tc26::Tests_t       m_allTests;

    // МПР
    tc26::Decisions_t   m_decisions;

    // Внешние методы
    void setAlphaParameter(const double &alpha);
    bool getTestsResult() const;

    friend class Console;

private:
    // Нужные файлы (файлы для тестирования
    // + выходной файл с результатами)
    tc26::StreamsCheck_t    m_openFiles;
    std::fstream            m_resultFile;

    // Таблица с pvalue
    tc26::ResultTable_t     m_pvalues;

    // Методы
    void Logic();
    void ParsingTests(QString dest);
    void ParsingDecisions(QString dest);

    // Нужные переменные
    bool                    m_isAllFileChecked;
    double                  m_alphaParameter;
};

#endif // CORE_HPP

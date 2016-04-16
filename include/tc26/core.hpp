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
    tc26::UsedTests_t       m_useTests;
    tc26::UsedTests_t       m_allTests;

    // Параметр окончания проверки всех файлов
    bool                    m_isAllChecked;

    friend class Console;

private:

    // Нужные файлы (файлы для тестирования
    // + выходной файл с результатами)
    tc26::StreamsCheck_t    m_openFiles;
    std::fstream            m_resultFile;



    // МПР
    tc26::UsedDecisions_t   m_useDecisions;
    tc26::UsedDecisions_t   m_allDecisions;

    // Таблица с pvalue
    tc26::ResultTable_t     m_pvalues;

    // Методы
    void Logic();
    void ParsingTests(QString dest);
    void ParsingDecisions(QString dest);
};

#endif // CORE_HPP

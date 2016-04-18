#include "include/tc26/core.hpp"
#include "include/tc26/utility.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <QDir>
#include <QCoreApplication>
#include <QLibrary>
#include <QString>
#include <QStringList>

Core::Core()
{
    m_isAllFileChecked = 0;
    m_alphaParameter = 0;
    ParsingTests("../TC26-STS/libs/statistical_tests");
    ParsingDecisions("../TC26-STS/libs/decisions");
    // TODO: функция для выбора файлов для тестирования
    // TODO: функция для заполнения выбранных тестов
}

Core::~Core()
{
    for(auto &file: m_openFiles)
    {
        file.first->close();
        (file.second).fileName.clear();
    }
    m_openFiles.clear();
    m_useTests.clear();
    m_allTests.clear();
    m_decisions.clear();
}

void Core::setAlphaParameter(const double &alpha)
{
    m_alphaParameter=alpha;
}

bool Core::getTestsResult() const
{
    return m_isAllFileChecked;
}

void Core::Logic()
{
    // Идём по открытым файлам (потокам)
    for(auto& currentStream: m_openFiles)
    {
        // Идём по выбранным тестам
        for(auto& currentTest: m_useTests)
        {
            std::vector<double> CurPvalues;
            while(*currentStream.first)
            {
                CurPvalues.push_back((*currentTest.m_func)
                                     (*currentStream.first,
                                      currentTest.m_testParameters.first,
                                      currentTest.m_testParameters.second));
            }
            currentStream.first->clear();
            currentStream.first->seekg(0);
            // Сортируем и запиливаем полученный вектор p-value в общую таблицу
            std::sort(CurPvalues.begin(), CurPvalues.end());
            m_pvalues.push_back(CurPvalues);

            // Идём по модулям принятия решений
            std::cout << "Decision Rule:\n";
            for(auto& currentDecision: m_decisions)
            {
                if ((*currentDecision.m_func)(CurPvalues, m_alphaParameter))
                    continue;
                else  
                {
                    (currentStream.second).testResult=0;
                    break;
                }
            }
            std::cout << "Decision Rule end.\n";
        }

        // Всё хорошо, все тесты выполнены и поток успешно
        // прошёл через тесты модуля принятия решения
        (currentStream.second).testResult=1;
    }
    m_isAllFileChecked = 1;
}

void Core::ParsingTests(QString dest)
{
    QDir dir(dest);
    QStringList filters;
    filters << "*.so" << "*.dll" << "*.DLL";
    QStringList plugins=dir.entryList(filters);
    for(auto& el:plugins)
    {
        QString plugin=el.right(el.size()-3);   //обрезка lib в названии
        plugin=plugin.section('.',0,0);         //обрезка расширения
        QLibrary lib(QString(dest).append(SLASH).append(plugin));
        if (!lib.load()) std::cout << lib.isLoaded() << ' ' << lib.errorString().toStdString() << '\n';
        tc26::TestFunc_t* fct = new tc26::TestFunc_t ((tc26::TestFunc_t)(lib.resolve(plugin.toStdString().c_str())));
        if(!fct) std::cout << lib.errorString().toStdString() << '\n';
        m_allTests.emplace_back(tc26::TestObj(*fct,(std::pair<int,char**>){0,NULL},plugin.toStdString()));
    }
}

void Core::ParsingDecisions(QString dest)
{
    QDir dir(dest);
    QStringList filters;
    filters << "*.so" << "*.dll" << "*.DLL";
    QStringList plugins=dir.entryList(filters);
    for(auto& el:plugins)
    {
        QString plugin=el.right(el.size()-3);//обрезка lib в названии
        plugin=plugin.section('.',0,0);//обрезка расширения
        QLibrary lib(QString(dest).append(SLASH).append(plugin));
        if (!lib.load()) std::cout << lib.isLoaded() << ' ' << lib.errorString().toStdString() << '\n';
        tc26::DeсisionFunc_t* fct = new tc26::DeсisionFunc_t((tc26::DeсisionFunc_t)(lib.resolve(plugin.toStdString().c_str())));
        if(!fct) std::cout << lib.errorString().toStdString() << '\n';
        m_decisions.emplace_back(tc26::DecisionObj(*fct, plugin.toStdString()));
    }
}

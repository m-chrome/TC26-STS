#include "include/tc26/core.hpp"

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
    m_isAllChecked = 0;
    ParsingTests("~/libs/statistical_tests");
    ParsingDecisions("~/libs/decisions");
    // TODO: функция для выбора файла для тестирования
    // TODO: функция для заполнения выбранных тестов
    // TODO: функция для заполнения выбранных решений
    Logic();
}

Core::~Core()
{
    m_openFiles.clear();
    m_useTests.clear();
    m_useDecisions.clear();
    m_allTests.clear();
    m_allDecisions.clear();
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
            while(currentStream.first)
            {
                CurPvalues.push_back((*currentTest.m_func)
                                     (currentStream.first,
                                      currentTest.m_testParameters.first,
                                      currentTest.m_testParameters.second));
            }

            // Сортируем и запиливаем полученный вектор p-value в общую таблицу
            std::sort(CurPvalues.begin(), CurPvalues.end());
            m_pvalues.push_back(CurPvalues);

            // Идём по модулям принятия решений
            for(auto& currentDecision: m_useDecisions)
            {
                if ((*currentDecision.m_func)(CurPvalues, currentDecision.m_alpha))
                    continue;
                else  
                {
                    (currentStream.second).testResult=0;
                    break;
                }
            }
        }

        // Всё хорошо, все тесты выполнены и поток успешно
        // прошёл через тесты модуля принятия решения
        (currentStream.second).testResult=1;
    }
    m_isAllChecked = 1;
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
        QLibrary lib(plugin);
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
        QLibrary lib(plugin);
        if (!lib.load()) std::cout << lib.isLoaded() << ' ' << lib.errorString().toStdString() << '\n';
        tc26::DeсisionFunc_t* fct = new tc26::DeсisionFunc_t((tc26::DeсisionFunc_t)(lib.resolve(plugin.toStdString().c_str())));
        if(!fct) std::cout << lib.errorString().toStdString() << '\n';
        m_allDecisions.emplace_back(tc26::DecisionObj(*fct, 0,(std::pair<int,char**>){0,NULL},plugin.toStdString()));
    }
}

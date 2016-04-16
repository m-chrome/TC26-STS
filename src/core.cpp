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

}

Core::~Core()
{
    m_openFiles.clear();
    m_tests.clear();
    m_decisions.clear();
}

void Core::Logic()
{
    // Идём по открытым файлам (потокам)
    for(auto& currentStream: m_openFiles)
    {
        // Идём по выбранным тестам
        for(auto& currentTest: m_tests)
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
            for(auto& currentDecision: m_decisions)
            {
                if ((*currentDecision.m_func)(CurPvalues, currentDecision.m_alfa))
                    std::cout << "success";
                else
                {
                    std::cout << "fail";
                    currentStream.second=0;
                }
            }
        }
        // Всё хорошо, все тесты выполнены и поток успешно
        // прошёл через тесты модуля принятия решения
        currentStream.second=1;
    }
}

void Core::Parsing(char* dest)
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
        tc26::TestFunc_t* fct = new tc26::TestFunc_t ((tc26::TestFunc_t)(lib.resolve(plugin.toStdString().c_str())));
        if(!fct) std::cout << lib.errorString().toStdString() << '\n';
        m_allTests.emplace_back(tc26::TestObj(*fct,(std::pair<int,char**>){0,NULL},plugin.toStdString()));
    }
}

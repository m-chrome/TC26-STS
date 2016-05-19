#include "include/tc26/core.hpp"
#include "include/tc26/utility.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <QDir>
#include <QLibrary>
#include <QString>
#include <QStringList>

Core::Core(const char* path)
{
    CreateUtilityTable(path);
    m_isAllFileChecked = 0;
    m_alphaParameter = 0;
    ParsingTests("../TC26-STS/libs/statistical_tests");
    ParsingDecisions("../TC26-STS/libs/decisions");
    // Костыль. Надо решить, как сортировать decisions в нужном порядке
    std::swap(m_decisions[0], m_decisions[1]);
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

tc26::Tests_t& Core::getAllTests()
{
    return m_allTests;
}

tc26::Tests_t& Core::getUseTests()
{
    return m_useTests;
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
            for(auto& currentDecision: m_decisions)
            {
                // Записываем тест и результат его проверки (по умочанию - false)
                (currentStream.second).testResults.emplace(currentTest.m_testName, false);
                if ((*currentDecision.m_func)(CurPvalues, m_alphaParameter))
                    // МПР прошёл - изменить результат на true
                    (currentStream.second).testResults.find(currentTest.m_testName)->second = true;
                else  
                {
                    // МПР не прошёл - изменить на false и сразу закончить проверку
                    (currentStream.second).testResults.find(currentTest.m_testName)->second = false;
                    break;
                }
            }
        }
    }
    // Всё хорошо, для каждого файла выполнены
    // все тесты и их результаты провереты модулем принятия решений
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

bool Core::CreateUtilityTable(const char* path)
{
    std::ifstream uT(path);
    if(uT.bad()) return false;
    char sym, temp[255];
    int count;
    while(uT)
    {
        uT.get(sym);
        if(sym=='#')
        {
            ClearStr(temp);
            uT.getline(temp,255);
            continue;
        }
        if(sym=='\n') continue;
        uT.unget();
        std::pair<std::string,testInfo> newEl;
        ClearStr(temp);
        uT.getline(temp,255,' ');
        newEl.first=std::string(temp);
        if(!(uT >> count)) return false;
        newEl.second.t_argc=count;
        ClearStr(temp);
        uT.getline(temp,255);
        newEl.second.description=std::string(temp);
        utilityTable.emplace(newEl);
    }
    uT.close();
    return true;
}

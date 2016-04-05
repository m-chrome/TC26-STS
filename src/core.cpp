#include <iostream>
#include <vector>
#include <algorithm>
#include "include/tc26/core.hpp"

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


#include <iostream>
#include <vector>
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
        // Таблица pvalue n*m, где
        // n - количество выбранных тестов
        // m - 100, количество подпоследовательностей, на которые мы разбиваем
        // Нужна ли она нам? Пусть будет

        // Идём по выбранным тестам
        for(auto& currentTest: m_tests)
        {
            std::set<double> CurPvalues;
            while(currentStream.first)
            {
                CurPvalues.insert((*currentTest.m_func)
                                     (currentStream.first,
                                      currentTest.m_testParameters.first,
                                      currentTest.m_testParameters.second));
            }
            // Запиливаем полученный вектор p-value в общую таблицу
            m_pvalues.push_back(CurPvalues);

            // Идём по модулям принятия решений
            for(auto& currentDecision: m_decisions)
            {
                if ((*currentDecision.m_func)(CurPvalues,currentDecision.m_alfa))
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


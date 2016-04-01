#include <vector>
#include "include/tc26/core.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::logic()
{
    // Идём по открытым файлам (потокам)
    for(auto& currentStream: openFiles_)
    {
        // Таблица pvalue n*m, где
        // n - количество выбранных тестов
        // m - 100, количество подпоследовательностей, на которые мы разбиваем
        // Нужна ли она нам? Пусть будет
        std::vector<std::vector<double>> resultPvalues;

        // Идём по выбранным тестам
        for(auto& currentTest: tests_)
        {
            std::vector<double> VecPvalues;
            while(currentStream.first)
            {
                VecPvalues.push_back((*currentTest.func)
                                     (currentStream.first,
                                      currentTest.testParameters.first,
                                      currentTest.testParameters.second));
            }
            // Запиливаем полученный вектор p-value в общую таблицу
            resultPvalues.push_back(VecPvalues);

            // Идём по модулям принятия решений
            for(auto& currentDecision: decisions_)
            {
                if ((*currentDecision.func)(VecPvalues,currentDecision.alfa))
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


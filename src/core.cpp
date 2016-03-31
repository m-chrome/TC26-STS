#include <vector>
#include "include/tc26/core.hpp"

Core::Core()
{
    //TODO
}

Core::~Core()
{

}

double Core::logic()
{
    for(auto& currentStream: openFiles_)
    {
        // идем по потокам
        // составляем список из Pvalues

        // Таблица pvalue n*m, где
        // n - количество выбранных тестов
        // m - 100, количество подпоследовательностей, на которые мы разбиваем
        // Нужна ли она нам? Пусть будет
        std::vector<std::vector<double>> resultPvalues;
        for(auto& currentTest: tests_)
        {
            std::vector<double> VecPvalues;
            while(currentStream)
            {
                VecPvalues.push_back((*currentTest.func)(currentStream, currentTest.testParameters.first, currentTest.testParameters.second));
            }
            // Запиливаем полученный вектор p-value в общую таблицу
            resultPvalues.push_back(VecPvalues);
            for(auto& currentDecision: decisions_)
            {
                if ((*currentDecision.func)(VecPvalues,currentDecision.alfa))
                {
                    std::cout << "success";
                }
                else
                {
                    std::cout << "fail";
                    break;
                }
            }
        }
    }
}


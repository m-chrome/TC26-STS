#include "include/tc26/core.hpp"
//#include <vector>

Core::Core()
{
    //TODO
}

Core::~Core()
{

}

double Core::logic(){
    for (auto& currentStream: openFiles_){// идем по потокам
        //std::vector<double> VecPvalues;
        //составляем список из Pvalues
        std::vector<std::vector<double>> resultPvalues; //итоговая табличка...вроде же.
        for (auto& currentTest: tests_){
            std::vector<double> VecPvalues;
            while(currentStream){
                VecPvalues.push_back((*currentTest.func)(currentStream, currentTest.testParameters.first, currentTest.testParameters.second));
            }
            for(auto& currentDecision: decisions_){
                if ((*currentDecision.func)(VecPvalues,currentDecision.alfa)){
                    std::cout << "success";
                }else{
                    std::cout << "fail";
                    break;
                }
            }
        }
    }
}


//
// Created by sunyh on 2020/11/19.
//
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class LLGrammaticalAnalyzer {
private:
    std::set<std::string> VT;//Terminal symbol
    std::set<std::string> VN;//Non-Terminal symbol
    std::map<std::string, std::set<std::string> > FIRST, FOLLOW;
    std::multimap<std::string, std::vector<std::string> > P;//production rules
    std::string START;

public:
    LLGrammaticalAnalyzer();

    void PrintProductionRules();
    void PrintFIRST();
    void PrintFOLLOW();

    void CalcFIRST();
    void CalcFOLLOW();
    void CreateTABLE();
    int CalcFIRSTSIZE();
    int CalcFOLLOWSIZE();
};
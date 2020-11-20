//
// Created by sunyh on 2020/11/19.
//

#include "GrammaticalAnalyzer.h"

LLGrammaticalAnalyzer::LLGrammaticalAnalyzer() {
//    ID,NUM
//
//    VT = {"{", "}", "if", "(", ")", "then", "else", "while", ">", "<", "<=", ">=", "==", "=", ";", "ID", "NUM"};
//    VN = {"program", "compoundstmt", "stmt", "ifstmt", "whilestmt", "assgstmt",
//          "stmts", "boolexpr", "arithexpr", "multexpr", "arithexprprime", "simpleexpr",
//          "multexprprime"};
//    P.insert({"program", {"compoundstmt"}});
//
//    P.insert({"stmt", {"ifstmt"}});
//    P.insert({"stmt", {"whilestmt"}});
//    P.insert({"stmt", {"assgstmt"}});
//    P.insert({"stmt", {"compoundstmt"}});
//
//    P.insert({"compoundstmt", {"{", "stmts", "}"}});
//
//    P.insert({"stmts", {"stmt", "stmts"}});
//    P.insert({"stmts", {"#"}});
//    P.insert({"ifstmt", {"if", "(", "boolexpr", ")", "then", "stmt", "else", "stmt"}});
//    P.insert({"whilestmt", {"while", "(", "boolexpr", ")", "stmt"}});
//    P.insert({"assgstmt", {"ID", "=", "arithexpr", ";"}});
//    P.insert({"boolexpr", {"arithexpr", "boolop", "arithexpr"}});
//    P.insert({"boolop", {"<"}});
//    P.insert({"boolop", {">"}});
//    P.insert({"boolop", {"<="}});
//    P.insert({"boolop", {">="}});
//    P.insert({"boolop", {"=="}});
//    P.insert({"arithexpr", {"multexpr", "arithexprprime"}});
//    P.insert({"arithexprprime", {"+", "multexpr", "arithexprprime"}});
//    P.insert({"arithexprprime", {"-", "multexpr", "arithexprprime"}});
//    P.insert({"arithexprprime", {"#"}});
//    P.insert({"multexpr", {"simpleexpr", "multexprprime"}});
//    P.insert({"multexprprime", {"*", "simpleexpr", "multexprprime"}});
//    P.insert({"multexprprime", {"/", "simpleexpr", "multexprprime"}});
//    P.insert({"multexprprime", {"#"}});
//    P.insert({"simpleexpr", {"ID", "NUM", "(", "arithexpr", ")"}});



//      ACCEPT

//    START = "S";
//    VT = {"if", "b", "other", "else", "then"};
//    VN = {"S", "I", "E", "L", "P", "O", "T"};
//
//    P.insert({"S", {"I", "E", "T", "S", "P"}});
//    P.insert({"S", {"O"}});
//    P.insert({"I", {"if"}});
//    P.insert({"E", {"b"}});
//    P.insert({"O", {"other"}});
//    P.insert({"L", {"else"}});
//    P.insert({"T", {"then"}});
//    P.insert({"P", {"L", "S"}});
//    P.insert({"P", {"#"}});


//      ACCEPT

//    VT={"i","+","-","*","/","(",")","="};
//    VN={"S","V","E","T","R","A","F","M","Y"};
//    START="S";
//    P.insert({"S",{"V","=","E"}});
//    P.insert({"E",{"T","R"}});
//    P.insert({"R",{"A","T","R"}});
//    P.insert({"R",{"#"}});
//    P.insert({"T",{"F","Y"}});
//    P.insert({"Y",{"M","F","Y"}});
//    P.insert({"Y",{"#"}});
//    P.insert({"F",{"(","E",")"}});
//    P.insert({"F",{"i"}});
//    P.insert({"A",{"+"}});
//    P.insert({"A",{"-"}});
//    P.insert({"M",{"*"}});
//    P.insert({"M",{"/"}});
//    P.insert({"V",{"i"}});
}

void LLGrammaticalAnalyzer::PrintProductionRules() {
    for (auto item:P) {
        std::cout << item.first << "->";
        for (auto i : item.second) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }
}

void LLGrammaticalAnalyzer::PrintFIRST() {
    for (auto item:FIRST) {
        std::cout << "FIRST(" << item.first << "):{";
        for (auto i : item.second) {
            std::cout << i << ' ';
        }
        std::cout << "}" << std::endl;
    }
}

int LLGrammaticalAnalyzer::CalcFIRSTSIZE() {
    int ret = 0;
    for (auto sym : FIRST) {
        ret += sym.second.size();
    }
    return ret;
}

int LLGrammaticalAnalyzer::CalcFOLLOWSIZE() {
    int ret = 0;
    for (auto sym : FOLLOW) {
        ret += sym.second.size();
    }
    return ret;
}

void LLGrammaticalAnalyzer::CalcFIRST() {
    for (std::string i : VT) {//if x in VT, FIRST(x)={x}
        FIRST[i].insert(i);
    }
    for (std::string i : VN) {
        auto rng = P.equal_range(i);
        auto iter = rng.first;
        auto end = rng.second;
        if (iter != std::end(P)) {
            while (iter != end) {
                if (std::find(iter->second.begin(), iter->second.end(), "#") != iter->second.end()) {
                    FIRST[i].insert("#");
                    break;
                } else
                    iter++;
            }
        }
    }
    int sz = CalcFIRSTSIZE();
    while (true) {
        for (auto rule:P) {
            std::string left = rule.first;
            std::vector<std::string> right = rule.second;
            for (std::string item: right) {
                std::set<std::string> tmp(FIRST[item].begin(), FIRST[item].end());
                tmp.erase("#");//without empty set
                FIRST[left].insert(tmp.begin(), tmp.end());
                if (!tmp.count("#")) {//without empty set
                    break;
                }
            }
        }
        int sz_t = CalcFIRSTSIZE();
        if (sz_t == sz) {//closure
            break;
        }
        sz = sz_t;
        //PrintFIRST();
        //std::cout<<sz<<std::endl;
    }
    //PrintFIRST();
}

void LLGrammaticalAnalyzer::PrintFOLLOW() {
    for (auto item:FOLLOW) {
        std::cout << "FOLLOW(" << item.first << "):{";
        for (auto i : item.second) {
            std::cout << i << ' ';
        }
        std::cout << "}" << std::endl;
    }
}

void LLGrammaticalAnalyzer::CalcFOLLOW() {
    //BEGIN WITH START

    FOLLOW[START].insert("#");


    int sz = CalcFOLLOWSIZE();
    while (true) {
        for (auto rule: P) {
            std::string left = rule.first;
            std::vector<std::string> right = rule.second;
            for (int i = 0; i < right.size(); i++) {
                std::string item = right[i];
                if (VT.count(item) > 0 || item == "#")// terminal
                    continue;
                if (i < right.size() - 1) {
                    std::string nxt = right[i + 1];
                    if (FIRST[nxt].count("#") > 0) {
                        FOLLOW[item].insert(FOLLOW[left].begin(), FOLLOW[left].end());
                    }

                    std::set<std::string> tmp(FIRST[nxt].begin(), FIRST[nxt].end());
                    tmp.erase("#");
                    FOLLOW[item].insert(tmp.begin(), tmp.end());

                } else {
                    FOLLOW[item].insert(FOLLOW[left].begin(), FOLLOW[left].end());
                }
            }
        }
        int sz_t = CalcFOLLOWSIZE();
        if (sz_t == sz) {//closure
            break;
        }
        sz = sz_t;
        //std::cout << sz << std::endl;
    }
    //PrintFOLLOW();
}

void LLGrammaticalAnalyzer::CreateTABLE(){
    
}
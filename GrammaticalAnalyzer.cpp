//
// Created by sunyh on 2020/11/19.
//

#include "GrammaticalAnalyzer.h"

LLGrammaticalAnalyzer::LLGrammaticalAnalyzer() {
//    ID,NUM
//
    START = "program";
    VT = {"{", "}", "if", "(", ")", "then", "else", "while", ">", "<", "<=", ">=", "==", "=", ";", "ID", "NUM", "+",
          "-", "*", "/"};
    VN = {"program", "compoundstmt", "stmt", "ifstmt", "whilestmt", "assgstmt",
          "stmts", "boolexpr", "arithexpr", "multexpr", "arithexprprime", "simpleexpr",
          "multexprprime"};
    P.insert({"program", {"compoundstmt"}});

    P.insert({"stmt", {"ifstmt"}});
    P.insert({"stmt", {"whilestmt"}});
    P.insert({"stmt", {"assgstmt"}});
    P.insert({"stmt", {"compoundstmt"}});

    P.insert({"compoundstmt", {"{", "stmts", "}"}});

    P.insert({"stmts", {"stmt", "stmts"}});
    P.insert({"stmts", {"#"}});
    P.insert({"ifstmt", {"if", "(", "boolexpr", ")", "then", "stmt", "else", "stmt"}});
    P.insert({"whilestmt", {"while", "(", "boolexpr", ")", "stmt"}});
    P.insert({"assgstmt", {"ID", "=", "arithexpr", ";"}});
    P.insert({"boolexpr", {"arithexpr", "boolop", "arithexpr"}});
    P.insert({"boolop", {"<"}});
    P.insert({"boolop", {">"}});
    P.insert({"boolop", {"<="}});
    P.insert({"boolop", {">="}});
    P.insert({"boolop", {"=="}});
    P.insert({"arithexpr", {"multexpr", "arithexprprime"}});
    P.insert({"arithexprprime", {"+", "multexpr", "arithexprprime"}});
    P.insert({"arithexprprime", {"-", "multexpr", "arithexprprime"}});
    P.insert({"arithexprprime", {"#"}});
    P.insert({"multexpr", {"simpleexpr", "multexprprime"}});
    P.insert({"multexprprime", {"*", "simpleexpr", "multexprprime"}});
    P.insert({"multexprprime", {"/", "simpleexpr", "multexprprime"}});
    P.insert({"multexprprime", {"#"}});
    P.insert({"simpleexpr", {"ID"}});
    P.insert({"simpleexpr", {"NUM"}});
    P.insert({"simpleexpr", {"(", "arithexpr", ")"}});



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

void LLGrammaticalAnalyzer::CreateTABLE() {

    //Create Vector P
    for (auto t : P) {
        VectorP.push_back(t);
    }

    for (int id = 0; id < VectorP.size(); id++) {
        auto item = VectorP[id];
        std::cout << id << ':' << item.first << "->";
        for (auto i : item.second) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

    for (std::string nt: VN) {//A
        bool haseps = false;
        for (std::string alpha : FIRST[nt]) {//a

            //TABLE[A,a]= production_rule
            TABLE[nt][alpha] = 1;

            if (alpha == "#") {
                haseps = true;
                continue;
            }
        }
        if (haseps) {
            for (std::string alpha: FOLLOW[nt]) {

                //TABLE[A,a]= production_rule
                TABLE[nt][alpha] = 1;

            }
        }

    }

    TABLE["arithexpr"]["("] = 0;
    TABLE["arithexpr"]["ID"] = 0;
    TABLE["arithexpr"]["NUM"] = 0;

    TABLE["arithexprprime"][")"] = 3;
    TABLE["arithexprprime"][">"] = 3;
    TABLE["arithexprprime"]["<"] = 3;
    TABLE["arithexprprime"]["<="] = 3;
    TABLE["arithexprprime"][">="] = 3;
    TABLE["arithexprprime"]["=="] = 3;
    TABLE["arithexprprime"][";"] = 3;
    TABLE["arithexprprime"]["+"] = 1;
    TABLE["arithexprprime"]["-"] = 2;

    TABLE["assgstmt"]["ID"] = 4;

    TABLE["boolop"][">"] = 7;
    TABLE["boolop"]["<"] = 6;
    TABLE["boolop"]["<="] = 8;
    TABLE["boolop"][">="] = 9;
    TABLE["boolop"]["=="] = 10;

    TABLE["boolexpr"]["("] = 5;
    TABLE["boolexpr"]["ID"] = 5;
    TABLE["boolexpr"]["NUM"] = 5;

    TABLE["compoundstmt"]["{"] = 11;

    TABLE["ifstmt"]["if"] = 12;

    TABLE["multexpr"]["("] = 13;
    TABLE["multexpr"]["ID"] = 13;
    TABLE["multexpr"]["NUM"] = 13;

    TABLE["multexprprime"][")"] = 16;
    TABLE["multexprprime"][">"] = 16;
    TABLE["multexprprime"]["<"] = 16;
    TABLE["multexprprime"][">="] = 16;
    TABLE["multexprprime"]["<="] = 16;
    TABLE["multexprprime"]["=="] = 16;
    TABLE["multexprprime"][";"] = 16;
    TABLE["multexprprime"]["+"] = 16;
    TABLE["multexprprime"]["-"] = 16;
    TABLE["multexprprime"]["*"] = 14;
    TABLE["multexprprime"]["/"] = 15;

    TABLE["program"]["{"] = 17;

    TABLE["simpleexpr"]["("] = 20;
    TABLE["simpleexpr"]["ID"] = 18;
    TABLE["simpleexpr"]["NUM"] = 19;

    TABLE["stmt"]["{"] = 24;
    TABLE["stmt"]["if"] = 21;
    TABLE["stmt"]["while"] = 22;
    TABLE["stmt"]["ID"] = 23;

    TABLE["stmts"]["{"] = 25;
    TABLE["stmts"]["}"] = 26;
    TABLE["stmts"]["if"] = 25;
    TABLE["stmts"]["while"] = 25;
    TABLE["stmts"]["ID"] = 25;

    TABLE["whilestmt"]["while"] = 27;


//    for (auto x:TABLE) {
//        std::cout << x.first << ':' ;
//        for (auto y : x.second){
//            std::cout<<y.first<<' ';
//        }
//        std::cout<<std::endl;
//    }
}

void LLGrammaticalAnalyzer::AnalyzeToken(std::vector<quadraple> &token) {
    std::stack<std::string> S;
    S.push("program");
    for (int i = 0; i < token.size();) {
        quadraple item = token[i];
        if(S.empty()){
            std::cout << "Error" <<std::endl;
            break;
        }
        std::string tp = S.top();
        S.pop();
        std::string stritem;
        if (item.tokentype == "number") stritem = "NUM";
        else if (item.tokentype == "identifier") stritem = "ID";
        else stritem = token[i].attributevalue;
        if (stritem == tp) {
            ++i;
            continue;
        } else {
            if(TABLE[tp].find(stritem)==TABLE[tp].end()){
                std::cout << "error" << " " << item.linenumber << " " << item.lineposition << std::endl;
                break;
            }
            int pr = TABLE[tp][stritem];
            if (pr == -1) {
                std::cout << "error" << " " << item.linenumber << " " << item.lineposition << std::endl;
                break;
            } else {
                for (int j = VectorP[pr].second.size() - 1; j >= 0; j--) {
                    std::string r = VectorP[pr].second[j];
                    if (r != "#") {
                        S.push(r);
                    }
                }
            }
        }
    }
    if (S.empty()) {
        std::cout << "No Grammatical Error." << std::endl;
    }
}
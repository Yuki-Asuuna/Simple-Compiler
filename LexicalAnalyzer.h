//
// Created by sunyh on 2020/11/16.
//
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <map>

class quadraple{
public:
    std::string tokentype,attributevalue;
    int linenumber;
    int lineposition;
    quadraple(std::string ,std::string ,int ,int );
};


class LexicalAnalyzer {

private:
    std::string source;
    std::vector<std::string> lines;
    std::map <std::string,bool> KEYWORD;
    std::vector<quadraple> result;
    std::vector<quadraple> error;

public:
    LexicalAnalyzer(std::string &);

    void CutLine(); //Cut Line with '\n' and remove empty line
    void RemoveComment();

    void PrintLines();

    void Parse();

    void AddWord(std::string &,int );

    std::vector <quadraple> GetResult();
    std::string categorize(std::string &);
};
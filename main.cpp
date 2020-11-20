#include <iostream>
#include "ReadProgram.h"
#include "LexicalAnalyzer.h"
#include "GrammaticalAnalyzer.h"

using namespace std;

void Lexical(string & source) {
    LexicalAnalyzer analyzer(source);
    analyzer.CutLine();
    analyzer.RemoveComment();
    analyzer.PrintLines();
    analyzer.Parse();
    auto r=analyzer.GetResult();
    for(auto item:r){
        cout<<'<'<<item.tokentype<<','<<item.attributevalue<<','<<item.linenumber<<','<<item.lineposition<<'>'<<endl;
    }
}

void Grammatical(){
    LLGrammaticalAnalyzer analyzer;
    //analyzer.PrintProductionRules();
    analyzer.CalcFIRST();
    analyzer.PrintFIRST();
    analyzer.CalcFOLLOW();
    analyzer.PrintFOLLOW();
    analyzer.CreateTABLE();
}

int main() {
    string source(ReadProgram());//source code read from file
    if (source.empty()) {//empty file or failed to open file
        return 0;
    }
    //cout<<source<<endl;

    //Lexical(source);
    Grammatical();


    return 0;
}

// #include "../production.h"
// #include "../LALR.h"
#if !defined(M_MAIN)
#define M_MAIN

#include "../production.cpp"
#include "../LALR.cpp"

// parseStringToProductions_t("A->C|dx|");

void testInit()
{
    readProductions("../file.txt");
    // buildProductionLefts();
}
void test()
{
    buildNullAble();
    buildFirst();
    buildFollow();
    buildSplitedIndex();
    buildFirst_sSet();
}

/*
"./file.txt"
*/
void process(string fileName)
{
    readProductions(fileName);

    // 文法build
    buildNullAble();
    buildFirst();
    buildFollow();
    buildSplitedIndex();
    buildFirst_sSet();
    // LR1相关build
    buildDFA();
    showLR1_DFA();
    cout << "LALR**************************************" << endl;
    makeLALR();
    showLALR_DFA();
    cout << "Ordered_LALR**************************************" << endl;
    buildMappingAndDfaitemsForLALR();
    buildDFA_LALR_ordered();
    showStandardSecondSheet(DFA_LALR_ordered, DFA_item_s_LALR_ordered);
    // 分析表
    cout << "AnalyseSheet:**************************************" << endl;
    buildAnalyseSheet();
    showAnalyzeSheet();
}

int main()
{
    process("./file.txt");
    recoveryForProduction();
    reocveryForLALR();
    // process("./file2.txt");
}

#endif // M_MAIN

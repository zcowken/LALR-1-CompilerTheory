#if !defined(MY_ALGOR_CPP)
#define MY_ALGOR_CPP

#include "myalgor.h"

void algor::process(string fileName, string matchFilePath) {
    // 创建一个引用 -- 方便使用
    ProductionUtil &ProductionUtil1 = this->lalrUtil1.ProductionUtil1;

    // 先回收后运行
    ProductionUtil1.recoveryForProduction();
    lalrUtil1.reocveryForLALR();

    ProductionUtil1.readProductions(fileName);
    // 文法build
    ProductionUtil1.buildNullAble();
    ProductionUtil1.buildFirst();
    ProductionUtil1.buildFollow();
    ProductionUtil1.buildSplitedIndex();
    ProductionUtil1.buildFirst_sSet();
    // LR1相关build
    lalrUtil1.buildDFA();
    cout << "LR1********************************************" << endl;
    lalrUtil1.showLR1_DFA();
    cout << "LALR**************************************" << endl;
    lalrUtil1.makeLALR();
    lalrUtil1.showLALR_DFA();
    cout << "Ordered_LALR**************************************" << endl;
    lalrUtil1.buildMappingAndDfaitemsForLALR();
    lalrUtil1.buildDFA_LALR_ordered();
    lalrUtil1.showStandardSecondSheet(lalrUtil1.DFA_LALR_ordered, lalrUtil1.DFA_item_s_LALR_ordered);

    cout << "LALR_ON_GEN***********************************" << endl;
    lalrUtil1.buildLALR_ON_GEN();

    // 分析表
    cout << "AnalyseSheet:**************************************" << endl;
    lalrUtil1.buildAnalyseSheet();
    lalrUtil1.showAnalyzeSheet();

    cout << "useAnalyseSheet*************************************" << endl;
    string matchFileName = matchFilePath;
    vector<string> analyseString = lalrUtil1.readStringLines(matchFileName);
    lalrUtil1.analyzeString(analyseString);

    cout << "AnalyseRecordList*************************************" << endl;
    lalrUtil1.showAnalyseRecordList();
}

#endif // MY_ALGOR_H

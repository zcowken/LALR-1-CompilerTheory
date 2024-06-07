// #if !defined(_ALGOR_CPP_)
// #define _ALGOR_CPP_

// #include "algor.h"

// void process(string fileName)
// {
//     // 先回收后运行
//     recoveryForProduction();
//     reocveryForLALR();

//     readProductions(fileName);
//     // 文法build
//     buildNullAble();
//     buildFirst();
//     buildFollow();
//     buildSplitedIndex();
//     buildFirst_sSet();
//     // LR1相关build
//     buildDFA();
//     showLR1_DFA();
//     cout << "LALR**************************************" << endl;
//     makeLALR();
//     showLALR_DFA();
//     cout << "Ordered_LALR**************************************" << endl;
//     buildMappingAndDfaitemsForLALR();
//     buildDFA_LALR_ordered();
//     showStandardSecondSheet(DFA_LALR_ordered, DFA_item_s_LALR_ordered);
//     // 分析表
//     cout << "AnalyseSheet:**************************************" << endl;
//     buildAnalyseSheet();
//     showAnalyzeSheet();
// }

// #endif // _ALGOR_CPP_

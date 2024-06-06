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

int main()
{
    testInit();
    test();
    // buildProductionLefts_t("../file.txt");
    // parseStringToProductions_t("Ac->Ba|d");
    // getSelectSet_s_t();
    buildDFA();
    showLR1_DFA();

    cout << "LALR**************************************" << endl;
    makeLALR();
    showLALR_DFA();
    cout << "Ordered_LALR**************************************" << endl;
    buildMappingAndDfaitemsForLALR();
    buildDFA_LALR_ordered();
    showStandardSecondSheet(DFA_LALR_ordered, DFA_item_s_LALR_ordered);
}

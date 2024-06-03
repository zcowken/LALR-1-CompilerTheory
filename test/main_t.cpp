#include "../production.cpp"
// parseStringToProductions_t("A->C|dx|");

void parseStringToProductions_t(string line)
{
    string left = line.substr(0, 1);
    if (line.find("->") != string::npos)
    {
        int pos = line.find("->") + string("->").length();
        string rights = line.substr(pos); // 右部的整体
        vector<string> parts;
        while (rights.find("|") != string::npos)
        {
            int pos2 = rights.find("|");
            string part_temp = rights.substr(0, pos2);
            parts.push_back(part_temp);
            rights.erase(0, part_temp.length() + string(("|")).length());
        }
        if (!rights.empty())
        {
            parts.push_back(rights);
        }
        else
        {
            throw new PRODUCTIONS_SENTENCE_ERROR();
        }
        // 存储回去
        for (string p_t : parts)
        {
            cout << p_t << endl;
        }
    }
    else
    {
        throw new PRODUCTIONS_SENTENCE_ERROR();
    }
}

void testInit()
{
    readProductions("../file.txt");
    buildProductionLefts();
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
}
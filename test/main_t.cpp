#include "../production.cpp"
#include "../LDLR.cpp"

// parseStringToProductions_t("A->C|dx|");

void parseStringToProductions_t(string line)
{
    int pos1 = line.find("->");
    string left = line.substr(0, pos1);
    if (line.find("->") != string::npos)
    {
        int pos = line.find("->") + string("->").length();
        string rights = line.substr(pos); // 右部的整体
        string rights_copy = rights;      // 右部的整体
        vector<string> parts;
        while (rights_copy.find("|") != string::npos)
        {
            int pos2 = rights_copy.find("|");
            string part_temp = rights_copy.substr(0, pos2);
            parts.push_back(part_temp);
            rights_copy.erase(0, part_temp.length() + string(("|")).length());
        }
        if (!rights_copy.empty())
        {
            parts.push_back(rights_copy);
        }
        else
        {
            throw new PRODUCTIONS_SENTENCE_ERROR();
        }
        // 存储回去
        for (string p_t : parts)
        {
            production production_temp;
            production_temp.left = left;
            for (int i = 0; i < p_t.size(); i++)
            {
                char c = p_t[i];
                int setFlag = false;
                int setLen = 1;
                string setElement = "";
                for (string le : productionLefts)
                {
                    int findPos = p_t.find(le);
                    if (findPos != string::npos && findPos == i)
                    {
                        setFlag = true;
                        setLen = le.size();
                        setElement = le;
                        break;
                    }
                }
                if (setFlag)
                {
                    i = i + setLen - 1;
                    production_temp.right.push_back(setElement);
                }
                else
                {
                    production_temp.right.push_back(string(1, c));
                }
            }
            production_temp.right2 = rights;
            productions.push_back(production_temp);
            // 输出
            cout << "productions中加入：" << production_temp.left << " \t" << p_t << endl;
        }
    }
    else
    {
        throw PRODUCTIONS_SENTENCE_ERROR();
    }
}

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

// 构建所有的文法左部
void buildProductionLefts_t(string fileName)
{
    // 旧写法，根据读入结果
    // for (int i = 0; i < productions.size(); i++)
    // {
    //     productionLefts.insert(productions[i].left);
    // }

    // 新写法
    // 先进行读入所有行的左部
    vector<string> lines;
    ifstream ifs(fileName);

    while (!ifs.eof())
    {
        char temp[BUFFER_SIZE];
        ifs.getline(temp, BUFFER_SIZE);
        string line(temp);
        lines.push_back(line);
    }

    // 开始处理
    // productionLefts
    cout << "开始构建左部集合：" << endl;
    for (string line : lines)
    {
        if (line.find("->") != string::npos)
        {
            int pos = line.find("->");
            productionLefts.insert(line.substr(0, pos));
        }
    }

    for (string p : productionLefts)
    {
        cout << p << endl;
    }
    cout << "左部end" << endl;
    ifs.close();
}

void getSelectSet_s_t()
{
    for (int i = 0; i < productions.size(); i++)
    {
        production p_t = productions[i];
        set<string> res = getSelectSet(p_t.right, set<string>(), p_t.left);

        cout << p_t.left << "独立函数计算的select集合" << setToString(res) << endl;
    }

    cout << "独立计算区域" << endl;
    /*
    独立区域测试原理
    A->(.A)的时候，会遇到A，需要推导下一个 A2-> .(A)  , ...的select集合
    */
    production p_t = productions[1];
    string newLeft = p_t.right[1];
    vector<string> temp1(p_t.right.begin() + 2, p_t.right.end());
    set<string> temp2;
    temp2.insert("$");
    set<string> res = getSelectSet(temp1, temp2, newLeft);
    cout << "产生下方式子的移近前文法:" << p_t.left << "->" << setToString(set<string>(p_t.right.begin() + 1, p_t.right.end())) << endl;
    cout << newLeft << "独立函数计算的select集合" << setToString(res) << endl;
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
}

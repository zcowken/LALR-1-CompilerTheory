#include "production.h"

#if !defined(_PRODUCTION_CPP_)
#define _PRODUCTION_CPP_



void parseStringToProductions(string line)
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

// 读入模块函数
void readProductions(string fileName)
{
    // 构建buildProductionLefts
    buildProductionLefts(fileName);

    vector<string> lines;
    ifstream ifs(fileName);

    while (!ifs.eof())
    {
        char temp[BUFFER_SIZE];
        ifs.getline(temp, BUFFER_SIZE);
        string line(temp);
        lines.push_back(line);
    }

    // 添加拓展文法
    string externProduction = "S'->" + lines[0].substr(0, lines[0].find("->")) + "$";
    productionLefts.insert("S'");

    lines.push_back("");
    for (int i = lines.size() - 1; i >= 1; i--)
    {
        lines[i] = lines[i - 1];
    }
    lines[0] = externProduction;

    // 开始处理
    for (string line : lines)
    {
        if (line.empty())
        {
            break;
        }
        parseStringToProductions(line);
    }

    // 展示所有读入的文法
    for (int i = 0; i < productions.size(); i++)
    {
        production p_t = productions[i];
        cout << "single splite line: " << p_t.left << " -> " << p_t.rightToString() << endl;
        for (int j = 0; j < p_t.right.size(); j++)
        {
            cout << p_t.left << "的:" << j << "-> β_j_item is: " << p_t.right[j] << endl;
        }
    }
}

// 构建所有的文法左部
void buildProductionLefts(string fileName)
{
    // 旧写法，根据读入结果
    // for (int i = 0; i < productions.size(); i++)
    // {
    //     productionLefts.insert(productions[i].left);
    // }

    // 新写法
    // 读入所有行
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

// 可以为空 的 文法左部
void buildNullAble()
{
    int preSize = -1;

    while (preSize != NullAble.size())
    {
        preSize = NullAble.size();
        for (production p_t : productions)
        {
            string b = p_t.right[0];
            if (productionLefts.find(b) != productionLefts.end())
            {
                // 如果B可以为空
                bool flag = true;
                for (string bi : p_t.right)
                {
                    // 如果是文法 -- 要求后续移进的文法全为空，才能判断当前文法可以为空
                    if (productionLefts.find(bi) != productionLefts.end())
                    {
                        flag = flag * (NullAble.find(bi) != NullAble.end());
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    NullAble.insert(p_t.left);
                }
            }
            else
            {
                if (b == CEIGEMA)
                {
                    NullAble.insert(p_t.left);
                }
            }
        }
    }
    cout << "可以为空的集合有：";
    for (string p : NullAble)
    {
        cout << p << endl;
    }
    cout << "空集合结束" << endl;
}
// 建立first和follow集合
void buildFirst()
{
    int changed = 1;

    while (changed == 1)
    {
        changed = 0;
        for (production p_t : productions)
        {
            string left = p_t.left;
            // 开始时候集合的大小
            int startSetSize = firstSet[left].size();
            for (string b : p_t.right) // 遍历一段文法的每一个字符
            {
                // b是下一个符号
                // 如果是集合
                if (productionLefts.find(b) != productionLefts.end())
                {
                    // 添加右部的frist
                    firstSet[left].insert(firstSet[b].begin(), firstSet[b].end());
                    // 如果b文法永远不空
                    if (NullAble.find(b) == NullAble.end())
                    {
                        break;
                    }
                    else
                    {
                        // 如果为空的话，需要下一轮循环，找到下一个b符号进行补充
                    }
                }
                else // 普通单词
                {
                    if (b == CEIGEMA)
                    {
                        // 如果为空，还是需要往后找
                        // 为了观察把，空符号补全
                        firstSet[left].insert(b);
                    }
                    else
                    {
                        firstSet[left].insert(b);
                        break;
                    }
                }
            }

            int endSetSize = firstSet[left].size();
            // 判断集合是否一致
            if (endSetSize != startSetSize)
            {
                changed = 1;
            }
        }
    }

    // 输出first集合
    for (string left : productionLefts)
    {
        cout << left << "文法的fist：" << setToString(firstSet[left]) << endl;
    }
}
void buildFollow()
{
    int changed = 1;

    while (changed == 1)
    {
        changed = 0;
        for (production p_t : productions)
        {
            string left = p_t.left;
            set<string> temp;
            // 开始时候所有集合的大小
            unordered_map<string, int> startSetSizeMap;
            for (string left_i : productionLefts)
            {
                startSetSizeMap[left_i] = followSet[left_i].size();
            }
            for (int i = p_t.right.size() - 1; i >= 0; i--) // 遍历一段文法的每一个字符(逆序的遍历)
            {
                // b是下一个符号
                string b = p_t.right[i];
                // 如果是集合
                if (productionLefts.find(b) != productionLefts.end())
                {
                    // 集合，加入后方已经计算过后的follow集合
                    followSet[b].insert(temp.begin(), temp.end());
                    // 如果这个文法b不会为空
                    if (NullAble.find(b) == NullAble.end())
                    {
                        temp = firstSet[b]; // 直接更新temp集合
                    }
                    else // 文法可以为空
                    {
                        // 那么，temp集合要额外补充b文法的first集合
                        set<string> b_first = firstSet[b];
                        temp.insert(b_first.begin(), b_first.end());
                    }
                }
                else // 普通单词
                {
                    if (b == CEIGEMA)
                    {
                        // 如果为空，还是需要往后找，但是不用放入follow
                        // 为了观察把，空符号补全
                        temp.insert(b);
                    }
                    else
                    {
                        temp.insert(b);
                    }
                }
            }

            // 结束时候所有集合的大小
            unordered_map<string, int> endSetSizeMap;
            // 判断集合是否一致
            for (string left_i : productionLefts)
            {
                endSetSizeMap[left_i] = followSet[left_i].size();

                if (endSetSizeMap[left_i] != startSetSizeMap[left_i])
                {
                    changed = 1;
                    break;
                }
            }
        }
    }

    // 输出follow集合
    for (string left : productionLefts)
    {
        cout << left << "文法的follow：" << setToString(followSet[left]) << endl;
    }
}

// 建立first_sSet集合
void buildSplitedIndex()
{
    for (int i = 0; i < productions.size(); i++)
    {
        // 定义索引从1开始
        SplitedIndex[productions[i].left][productions[i].rightToString()] = i;
        cout << productions[i].left << " \t " << productions[i].rightToString() << ":" << i + 1 << endl;
    }
}

// 全局构造fist_s
void buildFirst_sSet()
{
    for (production p_t : productions)
    {
        string left = p_t.left;
        // b是下一个符号
        int index = SplitedIndex[p_t.left][p_t.rightToString()];
        int withFollow = true;
        for (string b : p_t.right) // 遍历一段文法的每一个字符
        {
            // 如果是集合
            if (productionLefts.find(b) != productionLefts.end())
            {
                // 添加右部的frist
                first_sSet[index].insert(firstSet[b].begin(), firstSet[b].end());
                // 如果b文法永远不空
                if (NullAble.find(b) == NullAble.end())
                {
                    withFollow = false;
                    break; // 进入下一个文法
                }
                else
                {
                    // 如果为空的话，需要下一轮循环，找到下一个b符号进行补充
                }
            }
            else // 普通单词
            {
                if (b == CEIGEMA)
                {
                    // 如果为空，还是需要往后找，不退出
                    // 为了观察把，空符号补全
                    // first_sSet[index].insert(b);
                }
                else
                {
                    first_sSet[index].insert(b);
                    withFollow = false;
                    break; // 进入下一个文法
                }
            }
        }
        // 补充follow集合（如果前方都是文法，且每个文法都可能为空的话）
        if (withFollow)
        {
            first_sSet[index].insert(followSet[p_t.left].begin(), followSet[p_t.left].end());
        }
    }

    // 输出first_s集合
    for (int i = 0; i < productions.size(); i++)
    {
        production p_t = productions[i];
        int index = SplitedIndex[p_t.left][p_t.rightToString()];

        cout << p_t.left << " -> " << p_t.rightToString()
             << "的select集合为："
             << setToString(first_sSet[index]) << endl;
    }
}

set<string> getSelectSet(vector<string> betas, set<string> a, string left)
{
    set<string> ret;
    // 如果是集合
    for (int i = 0; i < betas.size(); i++)
    {
        string beta = betas[i];
        if (productionLefts.find(beta) != productionLefts.end())
        {
            // 添加右部的frist
            ret.insert(firstSet[beta].begin(), firstSet[beta].end());
            // 如果b文法永远不空
            if (NullAble.find(beta) == NullAble.end())
            {
                return ret;
            }
            else
            {
                // 如果为空的话，需要下一轮循环，找到下一个b符号进行补充
            }
        }
        else // 普通单词
        {
            if (beta == CEIGEMA)
            {
                // 如果为空，还是需要往后找，不退出
                // 为了观察把，空符号补全
                // ret.insert(beta);
            }
            else
            {
                ret.insert(beta);
                return ret; // 进入下一个文法
            }
        }
    }
    // 如果betas部分都可以是空
    ret.insert(a.begin(), a.end());
    // 如果a自己也是空
    if (a.empty())
    {
        ret.insert(followSet[left].begin(), followSet[left].end());
    }
    return ret;
}


#endif // _PRODUCTION_CPP_

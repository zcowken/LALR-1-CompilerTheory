#if !defined(_LDLR_CPP_)
#define _LDLR_CPP_
#include "LDLR.h"

void buildDFA()
{
    // 设置DFA表项信息
    DFA_item dfaItem1;
    dfaItem1.id = DFA_item_s.size();
    item item1;
    production p_t = productions[0];
    // 初始编号
    int p_t_index = SplitedIndex[p_t.left][p_t.rightToString()];
    // 为开头文法建立数据
    item1.index = p_t_index;
    item1.pos = 0;
    item1.select.insert("$");
    dfaItem1.items.push_back(item1);

    // 处理队列
    queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int curr = q.front();
        // 进行运算
        vector<item> newItems = DFA_item_s[curr].items;
        for (int i = 0; i < newItems.size(); i++)
        {
            item item_t = newItems[i];
            int pos = item_t.pos;
            int index = item_t.index;
            production p_t = productions[index];
            string nextPunc = p_t.right[pos];
            // 如果是非终结符
            if (productionLefts.find(nextPunc) != productionLefts.end())
            {
                for (pair<string, int> p : SplitedIndex[nextPunc])
                {
                    item newItem_t;
                    int newIndex = p.second;
                    production nextP_t = productions[newIndex];
                    // 设置基本信息
                    newItem_t.index = newIndex;
                    newItem_t.pos = 0;
                    // 寻找select集合
                    vector<string> betas(nextP_t.right.begin() + item_t.pos, nextP_t.right.end());
                    newItem_t.select = getSelectSet(betas, item_t.select, nextP_t.left);
                    // 判断是否存在相同的项目
                    bool isNew = true;
                    for (int j = 0; j < newItems.size(); j++)
                    {
                        item cmpItem = newItems[j];
                        if (isEqualForItem(newItem_t, cmpItem))
                        {
                            isNew = false;
                            break;
                        }
                    }

                    if (isNew)
                    {
                        newItems.push_back(newItem_t);
                    }
                }
            }
            else // 如果不是非终结符号
            {
                // 添加新边
            }
        }
    }

    // 记录
    DFA_item_s.push_back(dfaItem1);
}

bool isEqualForItem(item item1, item item2)
{
    if (item1.index != item2.index)
    {
        return false;
    }
    if (item1.pos != item2.pos)
    {
        return false;
    }
    set<string> temp1 = item1.select;
    set<string> temp2 = item2.select;
    // 大者在前
    if (temp1.size() < temp2.size())
    {
        swap(temp1, temp2);
    }
    temp1.erase(temp2.begin(), temp2.end());
    if (temp1.size() != 0)
    {
        return false;
    }
    return true;
}
#endif // _LDLR_CPP_

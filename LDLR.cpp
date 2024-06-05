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
    //  记录DFA_item
    DFA_item_s.push_back(dfaItem1);

    // 处理队列
    queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        // 进行运算，运算完成所有之后再寻找边
        vector<item> newItems = DFA_item_s[curr].items;
        for (int i = 0; i < newItems.size(); i++)
        {
            item item_t = newItems[i];
            int pos = item_t.pos;
            int index = item_t.index;
            production p_t = productions[index];
            string nextPunc = p_t.right[pos];
            // 如果是非终结符-- 移进加入
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
                    //
                    if (isNew)
                    {
                        production print_p_t = productions[newItem_t.index];
                        cout << "加入了" << print_p_t.left << " 的pos:" << newItem_t.pos << " -> "
                             << print_p_t.rightToString() << endl;
                        newItems.push_back(newItem_t);
                    }
                }
            }
        }
        // 将新的items赋值给原本的DFA_item
        DFA_item_s[curr].items = newItems;

        // 寻找完成所有的item之后，连接边，被链接的项目要创建完成，判断不存在之后，再进行连接
        // 遍历所有的文法
        DFA_item dfaItemForEdge = DFA_item_s[curr];
        // 寻找一个，然后更新到底
        for (int i = 0; i < dfaItemForEdge.items.size(); i++)
        {
            // item的基本信息
            item item_t = newItems[i];
            int pos = item_t.pos;
            int index = item_t.index;
            production p_t = productions[index];
            // 连接的边的信息
            string nextPunc = p_t.right[pos];

            // 准备新的DfaItem
            DFA_item addDfaItem;
            item addItem = item_t;
            item_t.pos += 1;
            addDfaItem.items.push_back(addItem);
            // 更新DfaItem
        }
        // 判断当前的DFA_item是否存在，如果存在，更新他
        // DFA_item newDfaItem1;
        // if (DFA[curr].find(nextPunc) != DFA[curr].end())
        // {
        //     newDfaItem1 = DFA_item_s[DFA[curr][nextPunc]];
        // }
        // else
        // {
        //     newDfaItem1.id = DFA_item_s.size();
        //     DFA_item_s.push_back(newDfaItem1);
        // }
        // item startItem1;
        // production p2_t = productions[item_t.index];
        // // 初始编号
        // int p2_t_index = SplitedIndex[p2_t.left][p2_t.rightToString()];
        // // 为开头文法建立数据
        // startItem1.index = p2_t_index;
        // startItem1.pos = item_t.pos + 1;
        // // 继承移进到选择区域的item的select集合
        // startItem1.select = item_t.select;
        // newDfaItem1.items.push_back(startItem1);

        // // 更新记录
        // DFA_item_s[newDfaItem1.id] = newDfaItem1;

        // // 添加新边
        // DFA[curr][nextPunc] = newDfaItem1.id;

        // // 加入处理队列
        // q.push(newDfaItem1.id);
    }
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

bool isEqualForDfaItem(DFA_item item1, DFA_item item2)
{
    if (item1.items.size() != item2.items.size())
    {
        return false;
    }
    int cnt = 0;
    int tar = item1.items.size();

    vector<item> items1 = item1.items;
    vector<item> items2 = item2.items;

    for (int i = 0; i < items1.size(); i++)
    {
        if (!isEqualForItem(items1[i], items2[i]))
        {
            return false;
        }
    }

    return true;
}

vector<item> generateNewItems(vector<item> items)
{
    vector<item> newItems = items;
    for (int i = 0; i < newItems.size(); i++)
    {
        item item_t = newItems[i];
        int pos = item_t.pos;
        int index = item_t.index;
        production p_t = productions[index];
        string nextPunc = p_t.right[pos];
        // 如果是非终结符-- 移进加入
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
                //
                if (isNew)
                {
                    production print_p_t = productions[newItem_t.index];
                    cout << "加入了" << print_p_t.left << " 的pos:" << newItem_t.pos << " -> "
                         << print_p_t.rightToString() << endl;
                    newItems.push_back(newItem_t);
                }
            }
        }
    }

    return newItems;
}

#endif // _LDLR_CPP_

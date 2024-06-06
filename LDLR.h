#include "production.cpp"
#include "queue"
#include <sstream>
#include<string.h>
#if !defined(_LDLR_H_)
#define _LDLR_H_

// 块
class item
{
public:
    int index;
    int pos;
    set<string> select;
    bool reduce = false;

    string toString()
    {
        stringstream ss;
        if (reduce)
        {
            ss << "reduce -- ";
        }
        ss << "index:" << this->index << "\t" << productions[this->index].rightToString() << '\t' << "pos" << this->pos << "\t" << "select:" << setToString(this->select);
        string s = ss.str();
        return s;
    }
};

// DFA的每个表项
class DFA_item
{
public:
    int id;
    vector<item> items;

    string toStringItems()
    {
        string res = "";
        for (item i : items)
        {
            res = res + i.toString() + "\n";
        }
        res.pop_back();
        return res;
    }
};

// DFA图的存储，二级索引广义表
int cntForDFA_item = 0;
unordered_map<int, unordered_map<string, int>> DFA;
// // DFA图的映射
// unordered_map<int, int> DFA_item_map;

// DFA图的项目的地址记录器
vector<DFA_item> DFA_item_s;

// 建图
void buildDFA();
// 判断两个 item 是否相等
bool isEqualForItem(item item1, item item2);

// 判断两个DFA_item是否相等
bool isEqualForDfaItem(DFA_item item1, DFA_item item2);

vector<item> generateNewItems(vector<item> items);

// 合并两个DfaItem
DFA_item mergeDfaItem(DFA_item item1, DFA_item item2);

// 展示LR(1)DFA
void showLR1_DFA();

// ERROR
class POSITION_VISIT_ERROR
{
};

#endif // _LDLR_H_

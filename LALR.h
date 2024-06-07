#ifndef LALR_H
#define LALR_H
#include "production.cpp"
#include"globals.cpp"
#include <sstream>
#include <string.h>
#include <queue>

// extern vector<production> productions;
// extern  set<string> productionLefts;
// extern set<string>  NullAble;
// extern unordered_map<string, set<string>> firstSet;
// extern unordered_map<string, set<string>> followSet;
// extern unordered_map<string, unordered_map<string, int>> SplitedIndex;
// extern unordered_map<int, set<string>> first_sSet;

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
        production p_t = productions[this->index];
        string leftString;
        for (int i = 0; i < p_t.right.size(); i++)
        {
            if (i == pos)
            {
                leftString = leftString + ".";
            }
            leftString = leftString + p_t.right[i];
        }
        if (reduce)
        {
            leftString += ".";
        }

        ss << "index:" << this->index << "\t" << p_t.left << "->" << leftString << '\t' << "pos" << this->pos << "\t" << "select:" << setToString(this->select);
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
        string res = "NodeId: " + to_string(id) + "\n";
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
unordered_map<int, unordered_map<string, int>> DFA_LALR;
unordered_map<int, unordered_map<string, int>> DFA_LALR_ordered;

// // DFA图的映射
// unordered_map<int, int> DFA_item_map;

// DFA图的项目的地址记录器
vector<DFA_item> DFA_item_s;
vector<DFA_item> DFA_item_s_LALR;
vector<DFA_item> DFA_item_s_LALR_ordered;

// 建图
void buildDFA();
// 判断两个 item 是否相等
bool isEqualForItem(item item1, item item2);

// 除去select集合外是否等价
bool isEqualForItemWithoutSelect(item item1, item item2);

// 判断两个DFA_item是否相等
bool isEqualForDfaItem(DFA_item item1, DFA_item item2);

// 生成所有可能推到出的item文法项目
vector<item> generateNewItems(vector<item> items);

// 化简一个DfaItem的items集合
vector<item> mergeDfaItemItems(vector<item> newItems);

// 合并两个DfaItem
void makeLALR();
int mergeDfaItem(int id1, int id2);
// 判断此id是否已经合并
bool lalrMerged[1024];

// 对化简后的LALR进行映射和重构
/**
 * first:有序的DFA_item的项目编号
 * second:DFA_item的id
 */
unordered_map<int, int> mappingForLALR;

// 构建映射表
void buildMappingAndDfaitemsForLALR();

// 构建有序的LALR的DFA
void buildDFA_LALR_ordered();

// 展示LR(1)DFA
void showLR1_DFA();

// 展示函数LALR
void showLALR_DFA();

// 展示ordered之后的LALR
void showStandardSecondSheet(unordered_map<int, unordered_map<string, int>> secondSheet, vector<DFA_item> dfaItems);

// 分析表的项目
enum SheetAction
{
    NONE,
    GOTO,
    SHIFT,
    REDUCE,
    ACCEPT,
};
unordered_map<int, string> SheetActionMapToStr = {{GOTO, "goto"}, {SHIFT, "shift"}, {REDUCE, "reduce"}, {ACCEPT, "Accept"}, {NONE, ""}};

class SheetItem
{
public:
    SheetAction sheetAction;
    int value;
    string toString()
    {
        if (sheetAction == SheetAction::REDUCE && value == 0)
        {
            return "Accept";
        }
        string ret;
        ret = SheetActionMapToStr[sheetAction] + to_string(value);
        return ret;
    }
};

// 表头的类型
enum SheetHeaderAction
{
    ACTION,
    GOTO_2
};
class SheetHeader
{
public:
    SheetHeaderAction sheetHeaderAction;
    string value;
};
// 分析表的表头（分别加入表头保证顺序）
vector<SheetHeader> analyseSheetHeader;
// 分析表
unordered_map<int, unordered_map<string, SheetItem>> analyseSheet;
// 创建分析表
void buildAnalyseSheet();
// 展示分析表
void showAnalyzeSheet();

// ERROR
class POSITION_VISIT_ERROR
{
};

// 回收
void reocveryForLALR();
#endif // LALR_H
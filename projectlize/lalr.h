#ifndef LALR_H
#define LALR_H
#define LALR_DEBUG_OUTPUT 0

#include <sstream>
#include <string.h>
#include <queue>
#include"production.h"
#include"globals.h"
#include "analyseRecord.h"
#include <iomanip>
#include <stack>

// 块
class item {
public:
//    ProductionUtil ProductionUtil1;
    production production1; // 记录此item的production信息（产生式信息）
    int index;
    int pos;
    set<string> select;
    bool reduce = false;
    int isCore = false; // 是否是文法的核心
    production self_pt; // 准备使用这个来存放数据，满足tostring的功能

    string toString() {
        stringstream ss;
        if (reduce) {
            ss << "reduce -- ";
        }
//        production p_t = ProductionUtil1.productions[this->index];
        production p_t = production1;
        string leftString;
        for (int i = 0; i < p_t.right.size(); i++) {
            if (i == pos) {
                leftString = leftString + ".";
            }
            leftString = leftString + p_t.right[i];
        }
        if (reduce) {
            leftString += ".";
        }

        ss << "index:" << this->index << "\t" << p_t.left << "->" << leftString << '\t' << "pos" << this->pos << "\t"
           << "select:" << setToString(this->select);
        if (isCore != 0) {
            ss << "\tisCore";
        }
        string s = ss.str();
        return s;
    }
};

// DFA的每个表项
class DFA_item {
public:
    int id;
    vector<item> items;

    string toStringItems() {
        string res = "NodeId: " + to_string(id) + "\n";
        for (item i: items) {
            res = res + i.toString() + "\n";
        }
        res.pop_back();
        return res;
    }

    vector<item> getCores() {
        vector<item> cores;
        int cnt = 0;
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].isCore) {
                cores.push_back(items[i]);
            }
        }
        return cores;
    }
};

// 表头的类型
enum SheetHeaderAction {
    ACTION,
    GOTO_2
};

class SheetHeader {
public:
    SheetHeaderAction sheetHeaderAction;
    string value;
};

// ERROR
class POSITION_VISIT_ERROR {
};


// 分析表的项目
enum SheetAction {
    NONE,
    GOTO,
    SHIFT,
    REDUCE,
    ACCEPT,
};


class SheetItem {
public:
    unordered_map<int, string> SheetActionMapToStr = {{GOTO,   "goto"},
                                                      {SHIFT,  "shift"},
                                                      {REDUCE, "reduce"},
                                                      {ACCEPT, "Accept"},
                                                      {NONE,   ""}};
    SheetAction sheetAction;
    int value;

    string toString() {
        if (sheetAction == SheetAction::REDUCE && value == 0) {
            return "Accept";
        }
        string ret;
        ret = SheetActionMapToStr[sheetAction] + to_string(value);
        return ret;
    }
};

class LALR {
public:
    ProductionUtil ProductionUtil1;

    // DFA图的存储，二级索引广义表
    int cntForDFA_item = 0;
    unordered_map<int, unordered_map<string, int>> DFA;
    unordered_map<int, unordered_map<string, int>> DFA_LALR;
    unordered_map<int, unordered_map<string, int>> DFA_LALR_ordered;

    // 合并方式优化-改为生成的时候进行合并,进行存储的位置
    unordered_map<int, unordered_map<string, int>> DFA_LALR_ON_GEN;
    unordered_map<int, unordered_map<string, int>> DFA_LALR_ON_GE_ordered;

    // // DFA图的映射
    // unordered_map<int, int> DFA_item_map;

    // DFA图的项目的地址记录器
    vector<DFA_item> DFA_item_s;
    vector<DFA_item> DFA_item_s_LALR;
    vector<DFA_item> DFA_item_s_LALR_ordered;
    vector<DFA_item> DFA_item_s_LALR_ON_GEN;

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

    // 判断一个DFA_item_s_LALR中的一个DFAItem，对应的此id是否已经合并
    bool lalrMerged[1024]; // 记录这lLR中的项目是否合并

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

    // 边生成边进行LALR的构造，但是现在已经废弃，因为递归合并法修好了
    void buildLALR_ON_GEN();

    // 根据LR1获取所有文法的核心和其核心对应的所有select集合
    vector<DFA_item> getCoreWithFullSelect();

    // 检验两个DFA_item的核心是否一致
    bool dfaItemCoreIsEqual(DFA_item dfaItem1, DFA_item dfaItem2);

    // 展示LR(1)DFA
    void showLR1_DFA();

    // 展示函数LALR
    void showLALR_DFA();

    // 展示ordered之后的LALR
    void showStandardSecondSheet(unordered_map<int, unordered_map<string, int>> secondSheet, vector<DFA_item> dfaItems);


    // 分析表的表头（分别加入表头保证顺序）
    vector<SheetHeader> analyseSheetHeader;
    // 分析表
    unordered_map<int, unordered_map<string, SheetItem>> analyseSheet; // 状态和指定字符串，到表的item

    // 分析过程
    vector<analyseRecord> analyseRecordList;

    // 创建分析表
    void buildAnalyseSheet();

    // 展示分析表
    void showAnalyzeSheet();

    // 获取分析内容
    vector<string>  readStringLines(string filePath);

    // 使用分析表进行字符串分析
    bool analyzeString(const vector<std::string> &inputStrings);

    // 展示分析的详细内容
    void showAnalyseRecordList();

    // 回收
    void reocveryForLALR();
};

#endif // LALR_H

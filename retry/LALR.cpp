#if !defined(_LALR_CPP_)
#define _LALR_CPP_
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
    dfaItem1.items = generateNewItems(dfaItem1.items);
    dfaItem1.items = mergeDfaItemItems(dfaItem1.items);
    //  记录DFA_item
    DFA_item_s.push_back(dfaItem1);

    // 处理队列
    queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        cout << "curr = " << curr << endl;
        cout << "curr msg:" << DFA_item_s[curr].toStringItems() << endl;

        // 进行运算，运算完成所有之后再寻找边
        // vector<item> newItems = DFA_item_s[curr].items;
        // newItems = generateNewItems(newItems);
        // // 将新的items赋值给原本的DFA_item
        // DFA_item_s[curr].items = newItems;

        // 寻找完成所有的item之后，才去连接边，被链接的项目要创建完成，判断不存在之后，再进行连接
        // 遍历所有的文法
        DFA_item dfaItemForEdge = DFA_item_s[curr];
        // 访问数组
        bool dfaItemForEdgeItemVis[1024];
        memset(dfaItemForEdgeItemVis, 0, sizeof(dfaItemForEdgeItemVis));
        // 遍历所有的文法，寻找一个，然后更新到底
        for (int i = 0; i < dfaItemForEdge.items.size(); i++)
        {
            // 如果是处理过的，跳过
            if (dfaItemForEdgeItemVis[i] == true)
            {
                continue;
            }
            dfaItemForEdgeItemVis[i] = true;

            // 准备处理某一条边的items
            vector<item> processItems;
            // item的基本信息
            item item_t = dfaItemForEdge.items[i];
            processItems.push_back(item_t);
            int pos = item_t.pos;
            int index = item_t.index;
            // 判断是否是归约项目，同时，归约项访问pos位置会越界，产生中断，所以要continue
            if (item_t.reduce)
            {
                continue;
            }
            production p_t = productions[index];

            // 连接的边的信息
            string nextPunc;
            if (p_t.right.size() > pos)
            {
                nextPunc = p_t.right[pos];
                // 寻找相同边的文法
                for (int j = 0; j < dfaItemForEdge.items.size(); j++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    item item_t_2 = dfaItemForEdge.items[j];
                    if (item_t_2.reduce) // 归约项目不加入
                    {
                        continue;
                    }
                    int pos2 = item_t_2.pos;
                    int index2 = item_t_2.index;
                    string nextPunc2 = productions[index2].right[pos2];
                    // 相同的下一个边，一起去处理
                    if (nextPunc2 == nextPunc)
                    {
                        dfaItemForEdgeItemVis[j] = true;
                        processItems.push_back(item_t_2);
                    }
                }
            }
            else
            {
                cout << "访问越界" << endl;
                throw POSITION_VISIT_ERROR();
            }

            // 准备新的DfaItem
            bool addNeedPush = true;
            DFA_item addDfaItem;
            for (int j = 0; j < processItems.size(); j++)
            {
                item addItem = processItems[j];
                addItem.pos += 1;
                addDfaItem.items.push_back(addItem);
            }

            // 更新DfaItem
            addDfaItem.items = generateNewItems(addDfaItem.items);
            addDfaItem.items = mergeDfaItemItems(addDfaItem.items);
            // 边不存在，准备添加边
            // 如果重复
            int findPos = -1;
            for (int j = 0; j < DFA_item_s.size(); j++)
            {
                if (isEqualForDfaItem(addDfaItem, DFA_item_s[j]))
                {
                    findPos = j;
                    break;
                }
            }
            // 如果重复-- 产生此节点的item连接到找到的位置
            if (findPos != -1)
            {
                // 重复的不加入队列
                DFA[dfaItemForEdge.id][nextPunc] = findPos;
                addNeedPush = false;
            }
            else // 不重复，直接加入，然后连接
            {
                addDfaItem.id = DFA_item_s.size();
                DFA_item_s.push_back(addDfaItem);
                DFA[dfaItemForEdge.id][nextPunc] = addDfaItem.id;
            }

            // 如果需要添加
            if (addNeedPush)
            {
                cout << "add to queue" << addDfaItem.id << endl;
                cout << "add msg: " << addDfaItem.toStringItems() << endl;
                q.push(addDfaItem.id);
            }
        }
        cout << "curr = " << curr << "\tend" << endl;
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
    vector<string> temp1 = vector<string>(item1.select.begin(), item1.select.end());
    vector<string> temp2 = vector<string>(item2.select.begin(), item2.select.end());
    // 大者在前
    if (temp1.size() != temp2.size())
    {
        return false;
    }
    for (int i = 0; i < temp1.size(); i++)
    {
        if (temp1[i] != temp2[i])
        {
            return false;
        }
    }

    return true;
}

bool isEqualForItemWithoutSelect(item item1, item item2)
{
    if (item1.index != item2.index)
    {
        return false;
    }
    if (item1.pos != item2.pos)
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
    cout << "开始补全" << endl;
    for (int i = 0; i < newItems.size(); i++)
    {
        item item_t = newItems[i];
        int pos = item_t.pos;
        int index = item_t.index;
        production p_t = productions[index];
        string nextPunc = "";
        if (p_t.right.size() > pos) // 尺寸足够
        {
            nextPunc = p_t.right[pos];
        }
        else // 尺寸不足
        {
            newItems[i].reduce = true; // 标上归约标志
            continue;
        }
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
                vector<string> betas(p_t.right.begin() + item_t.pos + 1, p_t.right.end());
                // debug
                // cout << "betas：" << endl;
                // for (auto i : betas)
                // {
                //     cout << i << " ";
                // }
                // cout << endl;

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
                    newItems.push_back(newItem_t);
                }
            }
        }
    }
    // debug
    for (auto i : newItems)
    {
        cout << i.toString() << endl;
    }

    cout << "结束补全" << endl;

    return newItems;
}

vector<item> mergeDfaItemItems(vector<item> newItems)
{
    vector<item> newItemsSimplify;
    // 合并后化简
    // 寻找合并项
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < newItems.size(); i++)
    {
        if (vis[i])
        {
            continue;
        }
        vis[i] = true;
        // 处理队列
        vector<item> v;
        // 找出此项目所有可以合并的项目
        for (int j = 0; j < newItems.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (isEqualForItemWithoutSelect(newItems[i], newItems[j]))
            {
                v.push_back(newItems[j]);
                vis[j] = true;
            }
        }

        // 开始合并select集合
        item temp = newItems[i];
        for (item item_i : v)
        {
            temp.select.insert(item_i.select.begin(), item_i.select.end());
        }
        newItemsSimplify.push_back(temp);
    }
    return newItemsSimplify;
}

void makeLALR()
{
    memset(lalrMerged, 0, sizeof(lalrMerged));
    DFA_LALR = DFA;
    DFA_item_s_LALR = DFA_item_s;

    // 根据返回的id更新DFA_LALR
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < DFA_item_s_LALR.size(); i++)
    {
        if (vis[i])
        {
            continue;
        }
        if (lalrMerged[i])
        {
            continue;
        }
        vis[i] = true;
        vector<int> v;
        for (int j = i + 1; j < DFA_item_s_LALR.size(); j++)
        {
            if (isEqualForItemWithoutSelect(DFA_item_s_LALR[i].items[0], DFA_item_s_LALR[j].items[0]))
            {
                v.push_back(j);
                vis[j] = true;
            }
        }
        // 更新
        for (int j = 0; j < v.size(); j++)
        {
            int resId = mergeDfaItem(i, v[j]);
            for (int id = 0; id < DFA_item_s_LALR.size(); id++)
            {
                // 除去被合并的项目
                if (id == i || id == v[j])
                {
                    continue;
                }
                unordered_map<int, std::unordered_map<std::string, int>> DFA_LALR_copy = DFA_LALR;
                for (pair<string, int> m : DFA_LALR_copy[id])
                {
                    // 更新为合并后的id
                    // 连接到合并项的，更改指向为新的id
                    if (DFA_LALR[id][m.first] == v[j])
                    {
                        DFA_LALR[id][m.first] = resId;
                    }
                }
            }
        }
    }
    // mergeDfaItem(3, 6);
    // mergeDfaItem(5, 2);
}

int mergeDfaItem(int id1, int id2)
{
    if (id1 == id2) // 合并自己的话，无需处理
    {
        return id1;
    }
    if (id1 > id2)
    {
        swap(id1, id2);
    }
    // 健康性
    if (lalrMerged[id1] || lalrMerged[id2])
    {
        return id1;
    }

    lalrMerged[id2] = true;
    // 递
    // 记录所有可以走的边
    set<string> edges;
    for (pair<string, int> edge : DFA_LALR[id1])
    {
        edges.insert(edge.first);
    }
    for (pair<string, int> edge : DFA_LALR[id2])
    {
        edges.insert(edge.first);
    }

    for (string edge : edges)
    {
        if ((DFA_LALR[id1].find(edge) != DFA_LALR[id1].end()) && (DFA_LALR[id2].find(edge) != DFA_LALR[id2].end()))
        {
            // 如果有相同的边
            // 递归合并
            // 如果是环边
            if (DFA_LALR[id1][edge] == id1)
            {
                // 小id的自环没关系
            }
            else if (DFA_LALR[id2][edge] == id2)
            {
                // 大id的自环，更新自环形式
                DFA_LALR[id1][edge] = id1;
            }
            else
            {
                int retId = mergeDfaItem(DFA_LALR[id1][edge], DFA_LALR[id2][edge]);
                DFA_LALR[id1][edge] = retId;
            }
        }
    }

    // 合并，化简
    vector<item> temp = DFA_item_s_LALR[id1].items;
    for (item i : DFA_item_s_LALR[id2].items)
    {
        temp.push_back(i);
    }
    DFA_item_s_LALR[id1].items = mergeDfaItemItems(temp);
    // 返回合并后的id1
    return id1;
}

void buildMappingAndDfaitemsForLALR()
{
    for (int i = 0, cnt = 0; i < DFA_item_s_LALR.size(); i++)
    {
        if (lalrMerged[i])
        {
            continue;
        }
        DFA_item dfaItem = DFA_item_s_LALR[i];
        mappingForLALR[dfaItem.id] = cnt;
        dfaItem.id = cnt;
        DFA_item_s_LALR_ordered.push_back(dfaItem);
        cnt++;
    }
}

void buildDFA_LALR_ordered()
{
    for (int id = 0; id < DFA_item_s_LALR.size(); id++)
    {
        if (lalrMerged[id])
        {
            continue;
        }
        // 遍历LALR的每一个节点
        for (pair<string, int> m : DFA_LALR[id])
        {
            string edge = m.first;
            int mappedId = mappingForLALR[id];
            DFA_LALR_ordered[mappedId][edge] = mappingForLALR[m.second];
        }
    }
}

void buildAnalyseSheet()
{
    // 准备加入表头
    set<string> VT;
    set<string> VN;

    // 遍历LALR的所有节点
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (vis[curr])
        {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = DFA_item_s_LALR_ordered[curr];

        // 处理归约项目
        // 遍历dfaItem.items的每一个项目,如果是归约,加入归约边,如果不是,就暂时不处理
        for (int i = 0; i < dfaItem.items.size(); i++)
        {
            // 如果是是归约项
            if (dfaItem.items[i].reduce)
            {
                // 准备添加reduce
                // 建立表项
                SheetItem sheetItem;
                set<string> edges = dfaItem.items[i].select;
                for (string edge : edges)
                {
                    VT.insert(edge);
                    // 给出归约的文法索引
                    sheetItem.value = dfaItem.items[i].index;
                    sheetItem.sheetAction = SheetAction::REDUCE;
                    analyseSheet[curr][edge] = sheetItem;
                }
            }
        }
        // 如果不是归约项,就不处理,直接压入,下一个处理节点
        // 层次加入连接了边的节点
        for (pair<string, int> m : DFA_LALR_ordered[curr])
        {
            string edge = m.first;
            int v = m.second;
            // push
            q.push(v);

            // 建立表项
            SheetItem sheetItem;
            // 如果是非终结符号
            if (productionLefts.find(edge) != productionLefts.end())
            {
                VN.insert(edge);
                sheetItem.value = v;
                sheetItem.sheetAction = SheetAction::GOTO;
            }
            else
            {
                VT.insert(edge);
                sheetItem.value = v;
                sheetItem.sheetAction = SheetAction::SHIFT;
            }
            analyseSheet[curr][edge] = sheetItem;
        }
    }

    // 建立表头（定义左边部分是终结符）
    for (string i : VT)
    {
        SheetHeader sheetHeader;
        sheetHeader.sheetHeaderAction = SheetHeaderAction::ACTION;
        sheetHeader.value = i;
        analyseSheetHeader.push_back(sheetHeader);
    }
    for (string i : VN)
    {
        SheetHeader sheetHeader;
        sheetHeader.sheetHeaderAction = SheetHeaderAction::GOTO_2;
        sheetHeader.value = i;
        analyseSheetHeader.push_back(sheetHeader);
    }
    cout << "表头为:";
    for (SheetHeader sha : analyseSheetHeader)
    {
        cout << sha.value << " ";
    }
    cout << endl;
}

void showAnalyzeSheet()
{
    cout << "sheetHeader\n\t";
    for (int i = 0; i < analyseSheetHeader.size(); i++)
    {
        cout << analyseSheetHeader[i].value << "\t";
    }
    cout << endl;
    for (int i = 0; i < DFA_item_s_LALR_ordered.size(); i++)
    {
        cout << "id:" << i << "\t";
        for (int j = 0; j < analyseSheetHeader.size(); j++)
        {
            SheetItem sheetItem = analyseSheet[i][analyseSheetHeader[j].value];
            cout << sheetItem.toString() << "\t";
        }
        cout << endl;
    }
}

void showLR1_DFA()
{
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (vis[curr])
        {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = DFA_item_s[curr];
        // 输出value
        cout << "----------- Node:" << curr << "--------------" << endl;
        cout << dfaItem.toStringItems() << endl;
        // 层次加入节点
        for (pair<string, int> m : DFA[dfaItem.id])
        {
            string edge = m.first;
            int v = m.second;
            cout << "Edge:" << m.first << "\t" << "to Node:" << v << endl;
            // push
            q.push(v);
        }
        cout << "---------------------------------------end" << endl;
    }
}

void showLALR_DFA()
{
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (vis[curr])
        {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = DFA_item_s_LALR[curr];
        // 输出value
        cout << "----------- Node:" << curr << "--------------" << endl;
        cout << dfaItem.toStringItems() << endl;
        // 层次加入节点
        for (pair<string, int> m : DFA_LALR[dfaItem.id])
        {
            if (lalrMerged[m.second])
            {
                continue;
            }
            string edge = m.first;
            int v = m.second;
            cout << "Edge:" << m.first << "\t" << "to Node:" << v << endl;
            // push
            q.push(v);
        }
        cout << "---------------------------------------end" << endl;
    }
}

void showStandardSecondSheet(unordered_map<int, unordered_map<string, int>> secondSheet, vector<DFA_item> dfaItems)
{
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (vis[curr])
        {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = dfaItems[curr];
        // 输出value
        cout << "----------- Node:" << curr << "--------------" << endl;
        cout << dfaItem.toStringItems() << endl;
        // 层次加入节点
        for (pair<string, int> m : secondSheet[curr])
        {
            string edge = m.first;
            int v = m.second;
            cout << "Edge:" << m.first << "\t" << "to Node:" << v << endl;
            // push
            q.push(v);
        }
        cout << "---------------------------------------end" << endl;
    }
}

void reocveryForLALR()
{
    // DFA
    DFA.clear();
    DFA_LALR.clear();
    DFA_LALR_ordered.clear();
    // items
    DFA_item_s.clear();
    DFA_item_s_LALR.clear();
    DFA_item_s_LALR_ordered.clear();
    // 化简后让编号顺序化的映射关系
    mappingForLALR.clear();
    memset(lalrMerged, 0, sizeof(lalrMerged));
    // 分析表
    analyseSheetHeader.clear();
    analyseSheet.clear();
}

#endif // _LALR_CPP_

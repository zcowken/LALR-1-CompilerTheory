#include "lalr.h"

#if !defined(_LALR_CPP_)
#define _LALR_CPP_

void LALR::buildDFA() {
    // 设置DFA表项信息
    DFA_item dfaItem1;
    dfaItem1.id = DFA_item_s.size(); // 一开始是0
    item item1;
    production p_t = ProductionUtil1.productions[0];
    // 初始编号
    int p_t_index = ProductionUtil1.SplitedIndex[p_t.left][p_t.rightToString()];
    // 为开头文法建立数据
    item1.index = p_t_index;
    item1.pos = 0;
    item1.select.insert("$");
    item1.production1 = p_t;
    item1.isCore = 1;
    dfaItem1.items.push_back(item1);
    dfaItem1.items = generateNewItems(dfaItem1.items);
    dfaItem1.items = mergeDfaItemItems(dfaItem1.items);
    //  记录DFA_item
    DFA_item_s.push_back(dfaItem1);

    // 处理队列
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
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
        for (int i = 0; i < dfaItemForEdge.items.size(); i++) {
            // 如果是处理过的，跳过
            if (dfaItemForEdgeItemVis[i] == true) {
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
            if (item_t.reduce) {
                continue;
            }
            production p_t = ProductionUtil1.productions[index];

            // 连接的边的信息
            string nextPunc;
            if (p_t.right.size() > pos) {
                nextPunc = p_t.right[pos];
                // 寻找相同边的文法
                for (int j = 0; j < dfaItemForEdge.items.size(); j++) {
                    if (i == j) {
                        continue;
                    }
                    item item_t_2 = dfaItemForEdge.items[j];
                    if (item_t_2.reduce) // 归约项目不加入
                    {
                        continue;
                    }
                    int pos2 = item_t_2.pos;
                    int index2 = item_t_2.index;
                    string nextPunc2 = ProductionUtil1.productions[index2].right[pos2];
                    // 相同的下一个边，一起去处理
                    if (nextPunc2 == nextPunc) {
                        dfaItemForEdgeItemVis[j] = true;
                        processItems.push_back(item_t_2);
                    }
                }
            } else {
                cout << "访问越界" << endl;
                throw POSITION_VISIT_ERROR();
            }

            // 准备新的DfaItem
            bool addNeedPush = true;
            DFA_item addDfaItem;
            for (int j = 0; j < processItems.size(); j++) {
                item addItem = processItems[j];
                addItem.pos += 1;
                addItem.isCore = 1;
                addDfaItem.items.push_back(addItem);
            }

            // 更新DfaItem
            addDfaItem.items = generateNewItems(addDfaItem.items);
            addDfaItem.items = mergeDfaItemItems(addDfaItem.items);
            // 边不存在，准备添加边
            // 如果重复
            int findPos = -1;
            for (int j = 0; j < DFA_item_s.size(); j++) {
                if (isEqualForDfaItem(addDfaItem, DFA_item_s[j])) {
                    findPos = j;
                    break;
                }
            }
            // 此次生成的DFA如果重复-- 产生此节点的item连接到找到的位置
            if (findPos != -1) {
                // 重复的不加入队列
                DFA[dfaItemForEdge.id][nextPunc] = findPos;
                addNeedPush = false;
            } else // 不重复，直接加入，然后连接
            {
                addDfaItem.id = DFA_item_s.size();
                DFA_item_s.push_back(addDfaItem);
                DFA[dfaItemForEdge.id][nextPunc] = addDfaItem.id;
            }

            // 如果需要添加
            if (addNeedPush) {
                cout << "add to queue" << addDfaItem.id << endl;
                cout << "add msg: " << addDfaItem.toStringItems() << endl;
                q.push(addDfaItem.id);
            }
        }
        cout << "curr = " << curr << "\tend" << endl;
    }
}

bool LALR::isEqualForItem(item item1, item item2) {
    if (item1.index != item2.index) {
        return false;
    }
    if (item1.pos != item2.pos) {
        return false;
    }
//    vector<string> temp1 = vector<string>(item1.select.begin(), item1.select.end());
//    vector<string> temp2 = vector<string>(item2.select.begin(), item2.select.end());
//    // 大者在前
//    if (temp1.size() != temp2.size()) {
//        return false;
//    }
    if (item1.select != item2.select) {
        return false;
    }
//    for (int i = 0; i < temp1.size(); i++) {
//        if (temp1[i] != temp2[i]) {
//            return false;
//        }
//    }
    return true;
}

bool LALR::isEqualForItemWithoutSelect(item item1, item item2) {
    // 判断是否为一个文法
    if (item1.index != item2.index) {
        return false;
    }
    // 判断此文法走到的下标位置是否一致
    if (item1.pos != item2.pos) {
        return false;
    }

    return true;
}

bool LALR::isEqualForDfaItem(DFA_item item1, DFA_item item2) {
    if (item1.items.size() != item2.items.size()) {
        return false;
    }

    vector<item> items1 = item1.items;
    vector<item> items2 = item2.items;

    for (int i = 0; i < items1.size(); i++) {
        if (!isEqualForItem(items1[i], items2[i])) {
            return false;
        }
    }

    return true;
}

vector<item> LALR::generateNewItems(vector<item> items) {
    vector<item> newItems = items;
    if(LALR_DEBUG_OUTPUT ==1)
    {
        cout << "开始补全" << endl;
    }
    for (int i = 0; i < newItems.size(); i++) {
        // 取出item数据
        item item_t = newItems[i];
        int pos = item_t.pos;
        int index = item_t.index;
        production p_t = ProductionUtil1.productions[index];
        string nextPunc = "";
        if (p_t.right.size() > pos) // 尺寸足够
        {
            nextPunc = p_t.right[pos];
        } else // 尺寸不足
        {
            newItems[i].reduce = true; // 标上归约标志
            continue;
        }
        // 如果是非终结符-- 移进加入
        if (ProductionUtil1.productionLefts.find(nextPunc) != ProductionUtil1.productionLefts.end()) {
            for (pair<string, int> p: ProductionUtil1.SplitedIndex[nextPunc]) {
                // 创建新的item
                item newItem_t;
                int newIndex = p.second;
                production nextP_t = ProductionUtil1.productions[newIndex];
                // 设置基本信息
                newItem_t.index = newIndex;
                newItem_t.pos = 0;
                newItem_t.production1 = nextP_t;
                // 寻找select集合
                // betas为下一位置开始直到结束
                vector<string> betas(p_t.right.begin() + item_t.pos + 1, p_t.right.end());
                // debug
                // cout << "betas：" << endl;
                // for (auto i : betas)
                // {
                //     cout << i << " ";
                // }
                // cout << endl;

                newItem_t.select = ProductionUtil1.getSelectSet(betas, item_t.select, nextP_t.left);
                // 判断是否存在相同的项目
                bool isNew = true;
                for (int j = 0; j < newItems.size(); j++) {
                    item cmpItem = newItems[j];
                    if (isEqualForItem(newItem_t, cmpItem)) {
                        isNew = false;
                        break;
                    }
                }
                //
                if (isNew) {
                    production print_p_t = ProductionUtil1.productions[newItem_t.index];
                    newItems.push_back(newItem_t);
                }
            }
        }
    }
    // debug
    if(LALR_DEBUG_OUTPUT == 1)
    {
        for (auto i: newItems) {
            cout << i.toString() << endl;
        }
        cout << "结束补全" << endl;
    }


    return newItems;
}

vector<item> LALR::mergeDfaItemItems(vector<item> newItems) {
    vector<item> newItemsSimplify;
    // 合并后化简
    // 寻找合并项
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < newItems.size(); i++) {
        if (vis[i]) {
            continue;
        }
        vis[i] = true;
        // 处理队列
        vector<item> v;
        // 找出此项目所有可以合并的项目
        for (int j = 0; j < newItems.size(); j++) {
            if (i == j) {
                continue;
            }
            if (isEqualForItemWithoutSelect(newItems[i], newItems[j])) {
                v.push_back(newItems[j]);
                vis[j] = true;
            }
        }

        // 开始合并select集合
        item temp = newItems[i];
        for (item item_i: v) {
            temp.select.insert(item_i.select.begin(), item_i.select.end());
        }
        newItemsSimplify.push_back(temp);
    }
    return newItemsSimplify;
}

void LALR::makeLALR() {
    memset(lalrMerged, 0, sizeof(lalrMerged));
    DFA_LALR = DFA;
    DFA_item_s_LALR = vector<DFA_item>(DFA_item_s);

    // 根据返回的id更新DFA_LALR
    bool vis[1024]; // 记录被合并的DFA_item_s_LALR的下标
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < DFA_item_s_LALR.size(); i++) {
        if (vis[i]) {
            continue;
        }
        if (lalrMerged[i]) {
            continue;
        }
        vis[i] = true;
        vector<int> v;
        for (int j = i + 1; j < DFA_item_s_LALR.size(); j++) {
            // 如果文法的核心是一致的
            if (isEqualForItemWithoutSelect(DFA_item_s_LALR[i].items[0], DFA_item_s_LALR[j].items[0])) {
                v.push_back(j);
                vis[j] = true;
            }
        }
        // 更新
        for (int j = 0; j < v.size(); j++) {
            int resId = mergeDfaItem(i, v[j]);
//            for (int id = 0; id < DFA_item_s_LALR.size(); id++) {
//                // 除去被合并的项目
//                if (id == i || id == v[j]) {
//                    continue;
//                }
//                unordered_map<int, std::unordered_map<std::string, int>> DFA_LALR_copy = DFA_LALR;
//                for (pair<string, int> m: DFA_LALR_copy[id]) {
//                    // 更新为合并后的id，连接到v[j]的都连接到被合并到的那个id去
//                    // 连接到合并项的，更改指向为新的id
//                    if (DFA_LALR[id][m.first] == v[j]) {
//                        DFA_LALR[id][m.first] = resId;
//                    }
//                }
//            }
        }
    }
    // mergeDfaItem(3, 6);
    // mergeDfaItem(5, 2);
}

int LALR::mergeDfaItem(int id1, int id2) {
    if (id1 == id2) // 合并自己的话，无需处理
    {
        return id1;
    }
    if (id1 > id2) {
        swap(id1, id2);
    }
    // 健康性
    if (lalrMerged[id1] || lalrMerged[id2]) {
        return id1;
    }

    lalrMerged[id2] = true;
    // 递
    // 记录所有可以走的边
    set<string> edges;
    for (pair<string, int> edge: DFA_LALR[id1]) {
        edges.insert(edge.first);
    }
    for (pair<string, int> edge: DFA_LALR[id2]) {
        edges.insert(edge.first);
    }

    // 巧合的原因，生成的点的数量是一样的，但是，实际上内容是错误的
    // 这里合并会出现递归之后，递归的第二层的DFAitem，如果被其他的DFAitem连接的话，无法补全连接的关系的问题
    // 解决方法1：在这里套用两层的for循环进行解决，将连接到被合并项目的，进行重新连接即可
    unordered_map<int, std::unordered_map<std::string, int>> DFA_LALR_copy = DFA_LALR;
    for (int id_link_to_id2 = 0; id_link_to_id2 < DFA_item_s_LALR.size(); id_link_to_id2++) {
        // 除去被合并的项目
        if (id_link_to_id2 == id1 || id_link_to_id2 == id2) {
            continue;
        }
        for (pair<string, int> m: DFA_LALR_copy[id_link_to_id2]) {
            // 更新为合并后的id，连接到v[j]的都连接到被合并到的那个id去
            // 连接到合并项的，更改指向为新的id
            if (DFA_LALR[id_link_to_id2][m.first] == id2) {
                DFA_LALR[id_link_to_id2][m.first] = id1;
            }
        }
    }

    for (string edge: edges) {
        if ((DFA_LALR[id1].find(edge) != DFA_LALR[id1].end()) && (DFA_LALR[id2].find(edge) != DFA_LALR[id2].end())) {
            // 如果有相同的边
            // 递归合并
            // 如果是环边
            if (DFA_LALR[id1][edge] == id1) {
                // 小id的自环没关系
            } else if (DFA_LALR[id2][edge] == id2) {
                // 大id的自环，更新自环形式
                DFA_LALR[id1][edge] = id1;
            } else {
                // 此次合并需要的操作执行完成后，然后再执行合并
                int retId = mergeDfaItem(DFA_LALR[id1][edge], DFA_LALR[id2][edge]);
                DFA_LALR[id1][edge] = retId;
            }
        }
    }

    // 合并，化简
    vector<item> temp = DFA_item_s_LALR[id1].items;
    for (const item &i: DFA_item_s_LALR[id2].items) {
        temp.push_back(i);
    }
    // 这一步确保了select集合的更新
    DFA_item_s_LALR[id1].items = mergeDfaItemItems(temp);
    // 返回合并后的id1
    return id1;
}

void LALR::buildMappingAndDfaitemsForLALR() {
    // 越过合并过的项目，重新赋值id序号，方便后期查看，mappingForLALR用于存储需要的映射
    for (int i = 0, cnt = 0; i < DFA_item_s_LALR.size(); i++) {
        if (lalrMerged[i]) {
            continue;
        }
        DFA_item dfaItem = DFA_item_s_LALR[i];
        mappingForLALR[dfaItem.id] = cnt;
        dfaItem.id = cnt;
        DFA_item_s_LALR_ordered.push_back(dfaItem);
        cnt++;
    }
}

void LALR::buildDFA_LALR_ordered() {
    for (int id = 0; id < DFA_item_s_LALR.size(); id++) {
        if (lalrMerged[id]) {
            continue;
        }
        // 遍历LALR的每一个节点
        for (pair<string, int> m: DFA_LALR[id]) {
            string edge = m.first;
            int mappedId = mappingForLALR[id];
            DFA_LALR_ordered[mappedId][edge] = mappingForLALR[m.second];
        }
    }
}

void LALR::buildLALR_ON_GEN() {
    // 设置DFA表项信息
    DFA_item dfaItem1;
    dfaItem1.id = DFA_item_s_LALR_ON_GEN.size(); // 一开始是0
    item item1;
    production p_t = ProductionUtil1.productions[0];
    // 初始编号
    int p_t_index = ProductionUtil1.SplitedIndex[p_t.left][p_t.rightToString()];
    // 为开头文法建立数据
    item1.index = p_t_index;
    item1.pos = 0;
    item1.select.insert("$");
    item1.production1 = p_t;
    dfaItem1.items.push_back(item1);
    dfaItem1.items = generateNewItems(dfaItem1.items);
    dfaItem1.items = mergeDfaItemItems(dfaItem1.items);
    //  记录DFA_item
    DFA_item_s_LALR_ON_GEN.push_back(dfaItem1);

    // 处理队列，记录DfaItem的id，记录的id所对应的DFAitem需要进行创建边的操作
    queue<int> q;
    q.push(0);

    // 根据LR1找到有哪些文法核心,然后重新生成
    vector<DFA_item> cores = getCoreWithFullSelect();
    //开始生成，直接根据核心生成表格
}

vector<DFA_item> LALR::getCoreWithFullSelect() {
    vector<DFA_item> itemCores;
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (vis[curr]) {
            continue;
        }
        vis[curr] = true;
        DFA_item dfaItem = DFA_item_s[curr];
        // 检验加入核心项目
        int mergeCore = false;
        for (int i = 0; i < itemCores.size(); i++) {
            DFA_item dfaItemOnlyCore = itemCores[i];
            // 如果有相同核心的文法项目，加入select集合
            if (dfaItemCoreIsEqual(dfaItemOnlyCore, dfaItem)) {
                for (int j = 0; j < dfaItemOnlyCore.items.size(); j++) {
                    set<string> addSelect = dfaItem.items[j].select;
                    // 加入集合
                    dfaItemOnlyCore.items[j].select.insert(addSelect.begin(), addSelect.end());
                }
                // 更新存储的核心值
                itemCores[i] = dfaItemOnlyCore;
                // 找到了一个核心值就可以了
                mergeCore = true;
                break;
            }
        }
        // 如果没有加入进去，就主动存储下来
        if (mergeCore == false) {
            DFA_item temp;
            temp.items = dfaItem.getCores();
            itemCores.push_back(temp);
        }
        // BFS-层次加入节点
        for (pair<string, int> m: DFA[dfaItem.id]) {
            int v = m.second;
            // push
            q.push(v);
        }
    }
    cout << "寻找到的核心数目有：" << itemCores.size() << "个！！" << endl;
    return itemCores;
}


bool LALR::dfaItemCoreIsEqual(DFA_item dfaItem1, DFA_item dfaItem2) {
    vector<item> cores1 = dfaItem1.getCores();
    vector<item> cores2 = dfaItem2.getCores();
    if (cores1.size() != cores2.size()) {
        return false;
    }
    for (int i = 0; i < cores1.size(); i++) {
        if (!isEqualForItemWithoutSelect(cores1[i], cores2[i])) {
            return false;
        }
    }
    return true;
}


void LALR::buildAnalyseSheet() {
    // 准备加入表头
    // 在此处再次进行构造的原因是，production中已经获取了VT和VN
    set<string> VT = ProductionUtil1.VT;
    set<string> VN = ProductionUtil1.productionLefts;

    // 遍历LALR的所有节点
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);

    // 记录需要空的边生成的表项目,对于他在的dfaItem的id，对所有非终结符号，进行reduce规约，规约方式为只含有空的那个item的左部
    vector<SheetItem> nullSheetItem;


    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (vis[curr]) {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = DFA_item_s_LALR_ordered[curr];

        // 处理归约项目
        // 遍历dfaItem.items的每一个项目,如果是归约,加入归约边,如果不是,就暂时不处理
        for (int i = 0; i < dfaItem.items.size(); i++) {
            // 如果是是归约项
            if (dfaItem.items[i].reduce) {
                // 准备添加reduce
                // 建立表项
                SheetItem sheetItem;
                set<string> edges = dfaItem.items[i].select;
                for (const string &edge: edges) {
                    VT.insert(edge);
                    // 给出归约的文法索引
                    sheetItem.value = dfaItem.items[i].index;
                    sheetItem.sheetAction = SheetAction::REDUCE;
                    analyseSheet[curr][edge] = sheetItem;
                }
            }
            // MARK 对空的处理
            // 如果右部只有一个空，对任何的符号(T-终结符)，允许直接规约，规约方式为自己的左部
            if (dfaItem.items[i].production1.right.size() == 1 &&
                dfaItem.items[i].production1.right[0] == ProductionUtil1.CEIGEMA) {
                // 建立表项
                SheetItem sheetItem;
                sheetItem.value = dfaItem.items[i].index;
                sheetItem.sheetAction = SheetAction::REDUCE;
                // 将此节点连接到的所有边设置为规约，然后，如果此节点还允许移进，在下方处理非规约的时候会覆盖掉。
                // 如果覆盖掉了，那么就可以认为此次发生了移进规约冲突（当然，一个文法不使用空，也会发生此冲突，
                // 只需满足规约在reduce中的sheetItem被覆盖掉，就是出现冲突
//                for(const string& vti: VT)
                // 但是呢，我们已经有能力计算含有空的select集合了，所以，无需使用VT进行加入，使用select集合即可
                for (const string &vti: dfaItem.items[i].select) {
                    analyseSheet[curr][vti] = sheetItem;
                }
            }
        }
        // 如果不是归约项,就不处理,直接压入,下一个处理节点
        // 层次加入连接了边的节点
        for (pair<string, int> m: DFA_LALR_ordered[curr]) {
            string edge = m.first;
            int v = m.second; // 经过边，到达的终点的DfaItem的id
            // push
            q.push(v);

            // 建立表项
            SheetItem sheetItem;
            // 如果是非终结符号
            if (ProductionUtil1.productionLefts.find(edge) != ProductionUtil1.productionLefts.end()) {
                VN.insert(edge);
                sheetItem.value = v;
                sheetItem.sheetAction = SheetAction::GOTO;
            } else {
                VT.insert(edge);
                sheetItem.value = v;
                sheetItem.sheetAction = SheetAction::SHIFT;
            }
            analyseSheet[curr][edge] = sheetItem;
        }
    }

    // 建立表头（定义左边部分是终结符）
    for (string i: VT) {
        SheetHeader sheetHeader;
        sheetHeader.sheetHeaderAction = SheetHeaderAction::ACTION;
        sheetHeader.value = i;
        analyseSheetHeader.push_back(sheetHeader);
    }
    for (string i: VN) {
        SheetHeader sheetHeader;
        sheetHeader.sheetHeaderAction = SheetHeaderAction::GOTO_2;
        sheetHeader.value = i;
        analyseSheetHeader.push_back(sheetHeader);
    }
    cout << "表头为:";
    for (SheetHeader sha: analyseSheetHeader) {
        cout << sha.value << " ";
    }
    cout << endl;
}

void LALR::showAnalyzeSheet() {
    cout << std::left;
    int outLen = 15;
    std::cout << "sheetHeader\n";
    cout << std::setw(outLen) << " ";
    for (int i = 0; i < analyseSheetHeader.size(); i++) {
        cout << std::setw(outLen) << analyseSheetHeader[i].value;//<< string (2,'\t');
    }
    cout << endl;
    for (int i = 0; i < DFA_item_s_LALR_ordered.size(); i++) {
        cout << std::setw(outLen) << "id:" + to_string(i);//<<  string (2,'\t');
        for (int j = 0; j < analyseSheetHeader.size(); j++) {
            SheetItem sheetItem = analyseSheet[i][analyseSheetHeader[j].value];
            cout << std::setw(outLen) << sheetItem.toString();// <<  string (2,'\t');
        }
        cout << endl;
    }
}

void LALR::showLR1_DFA() {
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (vis[curr]) {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = DFA_item_s[curr];
        // 输出value
        cout << "----------- Node:" << curr << "--------------" << endl;
        cout << dfaItem.toStringItems() << endl;
        // 层次加入节点
        for (pair<string, int> m: DFA[dfaItem.id]) {
            string edge = m.first;
            int v = m.second;
            cout << "Edge:" << m.first << "\t" << "to Node:" << v << endl;
            // push
            q.push(v);
        }
        cout << "---------------------------------------end" << endl;
    }
}

void LALR::showLALR_DFA() {
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (vis[curr]) {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = DFA_item_s_LALR[curr];
        // 输出value
        cout << "----------- Node:" << curr << "--------------" << endl;
        cout << dfaItem.toStringItems() << endl;
        // 层次加入节点
        for (pair<string, int> m: DFA_LALR[dfaItem.id]) {
            if (lalrMerged[m.second]) {
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

void
LALR::showStandardSecondSheet(unordered_map<int, unordered_map<string, int>> secondSheet, vector<DFA_item> dfaItems) {
    queue<int> q;
    bool vis[1024];
    memset(vis, 0, sizeof(vis));
    q.push(0);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (vis[curr]) {
            continue;
        }
        vis[curr] = true;

        DFA_item dfaItem = dfaItems[curr];
        // 输出value
        cout << "----------- Node:" << curr << "--------------" << endl;
        cout << dfaItem.toStringItems() << endl;
        // 层次加入节点
        for (pair<string, int> m: secondSheet[curr]) {
            string edge = m.first;
            int v = m.second;
            cout << "Edge:" << m.first << "\t" << "to Node:" << v << endl;
            // push
            q.push(v);
        }
        cout << "---------------------------------------end" << endl;
    }
}

void LALR::reocveryForLALR() {
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

vector<string> LALR::readStringLines(string filePath) {
    // 这种文件读入方法会自动忽略文件末尾的空行
    vector<string> readLines;
    ifstream ifs(filePath);
    string temp;
    while (getline(ifs, temp)) {
        readLines.push_back(temp);
    }
    ifs.close();
    return readLines;
}


bool LALR::analyzeString(const vector<std::string> &inputStrings) {
    analyseRecordList.clear(); // 情况分析表内容

    // 状态栈
    stack<int> statusStack;
    // 符号栈
    stack<string> characterStack;
    // 输入栈
    queue<string> inputQueue;
    // 加入符号栈
    inputQueue.push("$");
    for (string i: inputStrings) {
        inputQueue.push(i);
    }
    inputQueue.push("$");
    // 开始分析
    inputQueue.pop();
    characterStack.push("$");
    statusStack.push(0);

    int accpet = false;

    while (!inputQueue.empty()) {
        string curr = inputQueue.front();
        int state = statusStack.top();
        SheetItem sheetItem = analyseSheet[state][curr];
        int gotoState = -1;// 负1代表不goto
        // 记录当前的状态栈，符号栈情况，输入队列情况，然后填写动作
        analyseRecord record(statusStack, characterStack, inputQueue);
        record.lineId = analyseRecordList.size();
        record.action = sheetItem.toString();
        // goto的内容需要在下方进行回填
        if (sheetItem.sheetAction == SheetAction::NONE) {
            cout << "analyse failed" << endl;
            return false;
        } else if (sheetItem.sheetAction == SheetAction::SHIFT) {
            // 移进的时候，进行输入字符的弹出
            inputQueue.pop();
            int shiftState = sheetItem.value;
            // 加入状态
            statusStack.push(shiftState);
            // 加入字符
            characterStack.push(curr);
        } else if (sheetItem.sheetAction == SheetAction::GOTO) {
//            int gotoState = sheetItem.value;
//            statusStack.push(gotoState);
        } else if (sheetItem.sheetAction == SheetAction::REDUCE && sheetItem.value == 0) {
            gotoState = 0;
            accpet = true;
            cout << "到达成功点" << endl;
        } else if (sheetItem.sheetAction == SheetAction::REDUCE) {
            // 获取规约规则
            int productionIdx = sheetItem.value;
            production p_t = ProductionUtil1.productions[productionIdx];
            string left = p_t.left;
            // 弹出被归约的状态
            // 按照规约规则弹出字符集，然后压入规约项目
            for (int t = 0; t < p_t.right.size(); t++) {
                // 跳过空的弹出
                if (p_t.right[t] == ProductionUtil1.CEIGEMA) {
                    continue;
                }
                statusStack.pop();
                characterStack.pop();
            }
            int currState = statusStack.top();
            characterStack.push(left);
            // 获取进行reduce后进行goto的选项
            SheetItem sheetItemGoto = analyseSheet[currState][left];
            // 将goto的状态加入状态
            gotoState = sheetItemGoto.value;
            statusStack.push(gotoState);
        }
        // 填写goto的内容
        if (sheetItem.sheetAction == SheetAction::REDUCE) {
            record.gotoContent = "goto:" + to_string(gotoState);
        }
        analyseRecordList.push_back(record);
        if (accpet) {
            return true;
        }
    }
    return false;
}


void LALR::showAnalyseRecordList() {
    for (int i = 0; i < analyseRecordList.size(); i++) {
        cout << analyseRecordList[i].getDetails() << endl;
    }
}


#endif // _LALR_CPP_

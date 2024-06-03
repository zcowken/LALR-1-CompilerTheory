#if !defined(PRODUCTION_H)
#define PRODUCTION_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
#include "globals.h"

#define PRODUCTION_MAX_SIZE 1024
#define BUFFER_SIZE 1024
using namespace std;

const string CEIGEMA = "@";

class production
{
public:
    string left;
    vector<string> right;
    string right2; // 冗余字段

    string rightToString()
    {
        string temp = "";
        for (string si : this->right)
        {
            temp += si;
        }
        return temp;
    }
};

vector<production> productions;

// 所有的文法左部
set<string> productionLefts;

// 可以为空 的 文法左部
set<string> NullAble;

// first和follow集合
unordered_map<string, set<string>> firstSet;
unordered_map<string, set<string>> followSet;

// 索引表 -- 分割后的索引
// 定义索引从1开始
unordered_map<string, unordered_map<string, int>> SplitedIndex;
unordered_map<int, set<string>> first_sSet;

// 读入模块函数
void readProductions(string fileName);

// string读出为production
void parseStringToProductions(string line);

// 构建所有的文法左部
void buildProductionLefts();
// 可以为空 的 文法左部
void buildNullAble();
// 建立first和follow集合
void buildFirst();
void buildFollow();
// 建立first_sSet集合
void buildSplitedIndex();
void buildFirst_sSet();
// 错误列表
class PRODUCTIONS_SENTENCE_ERROR
{
    string message = "文法格式错误";
};

#endif // __PRODUCTION_H
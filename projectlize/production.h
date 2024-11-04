#if !defined(PRODUCTION_H)
#define PRODUCTION_H
#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>


#define PRODUCTION_MAX_SIZE 1024
#define BUFFER_SIZE 1024
using namespace std;

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
            temp = temp + si + " ";
        }
        return temp;
    }
};

class ProductionUtil{

public:
    const string CEIGEMA = "@";

    vector<production> productions;

    // 所有的文法左部
    set<string> productionLefts;

    // 可以为空 的 文法左部
    set<string> NullAble;

    // first和follow集合
    unordered_map<string, set<string>> firstSet;
    unordered_map<string, set<string>> followSet;

    // 索引表 -- 分割后的索引
    // 定义索引从0开始，记录的是左部对应的所有右部以及一个左部一个右部对应的productions所在的下标
    unordered_map<string, unordered_map<string, int>> SplitedIndex;
    unordered_map<int, set<string>> first_sSet;

    // 读入模块函数
    void readProductions(string fileName);

    // string读出为production
    void parseStringToProductions(string line);

    // 构建所有的文法左部
    void buildProductionLefts(string fileName);
    // 可以为空 的 文法左部
    void buildNullAble();
    // 建立first和follow集合
    void buildFirst();
    void buildFollow();
    // 建立first_sSet集合
    void buildSplitedIndex();
    void buildFirst_sSet();

    /**
 * betas：文法右部分（分割后）
 * pos，当前走到右部的位置
 * a，移进到当前文法的的文法的first集合
 * left，需要新的select集合的文法左部
 */
    set<string> getSelectSet(vector<string> betas, set<string> a, string left);

    // 回收初始化全局变量
    void recoveryForProduction();
};

// 错误列表
class PRODUCTIONS_SENTENCE_ERROR
{
public:
    string message = "文法格式错误";
};


#endif // __PRODUCTION_H

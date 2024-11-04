//
// Created by zken on 2024/11/4.
//
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include "util.h"

using namespace std;

#ifndef PROJECTLIZE_ANALYSERECORD_H
#define PROJECTLIZE_ANALYSERECORD_H

class analyseRecord {
public:
    int lineId;// 行号
    string statusStackStatus;//状态栈的状态
    string characterStackStatus;//符号栈栈的状态
    string inputQueueStatus;//输入队列的状态
    string action; // 进行的动作
    string gotoContent;//如果进行了reduce，那么要进行goto
    analyseRecord();

    analyseRecord(stack<int> status, stack<string> characterStatus, queue<string> inputQueueStatus);

    string getDetails();
};


#endif //PROJECTLIZE_ANALYSERECORD_H

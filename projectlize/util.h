//
// Created by zken on 2024/11/4.
//
#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;
#ifndef PROJECTLIZE_UTIL_H
#define PROJECTLIZE_UTIL_H


class util {
public:
    static string stackToString(stack<string> s)
    {
        string res = "";
        stack<string> t = stack<string>(s);
        while(!t.empty())
        {
            string s_t = t.top();
            t.pop();
            res = res + (s_t);
            res+=",";
        }
        return res;
    }
    static string stackToString(stack<int> s)
    {
        string res = "";
        stack<int> t = stack<int>(s);
        while(!t.empty())
        {
            int i = t.top();
            t.pop();
            res = res + to_string(i);
            res+=",";
        }
        return res;
    }
    static string queueToString(queue<string> q)
    {
        string res = "";
        queue<string>t =queue<string>(q);
        while(!t.empty())
        {
            string i = t.front();
            t.pop();
            res = res + i;
            res+=",";
        }
        return res;
    }
};


#endif //PROJECTLIZE_UTIL_H

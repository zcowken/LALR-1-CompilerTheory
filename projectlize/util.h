//
// Created by zken on 2024/11/4.
//
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
#ifndef PROJECTLIZE_UTIL_H
#define PROJECTLIZE_UTIL_H


class util {
public:
    static string stackToString(stack<string> s, int reverse1 = false) {
        string res = "";
        vector<string> v;
        // 拷贝
        stack<string> t = stack<string>(s);
        while (!t.empty()) {
            string s_t = t.top();
            t.pop();
            v.push_back(s_t);
        }
        if(reverse1)
        {
            reverse(v.begin(),v.end());
        }
        for(const string& vi: v)
        {
            res = res + (vi);
            res += ",";
        }

        return res;
    }

    static string stackToString(stack<int> s, int reverse1 = false) {
        string res = "";
        vector<string> v;
        // 拷贝
        stack<int> t = stack<int>(s);
        while (!t.empty()) {
            // int转字符串
            string s_t = to_string(t.top());
            t.pop();
            v.push_back(s_t);
        }
        if(reverse1)
        {
            reverse(v.begin(),v.end());
        }
        for(const string& vi: v)
        {
            res = res + (vi);
            res += ",";
        }
        return res;
    }

    static string queueToString(queue<string> q) {
        string res = "";
        queue<string> t = queue<string>(q);
        while (!t.empty()) {
            string i = t.front();
            t.pop();
            res = res + i;
            res += ",";
        }
        return res;
    }
};


#endif //PROJECTLIZE_UTIL_H

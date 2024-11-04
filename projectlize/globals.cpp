#ifndef GLOBALS_CPP
#define GLOBALS_CPP
#include"globals.h"

string setToString(set<string> s)
{
    string res = "{";
    for (string si : s)
    {
        res = res + si + ",";
    }
    res += "}";

    return res;
}
#endif

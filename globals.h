#if !defined(GLOABL_H)
#define GLOABL_H
#include <set>
#include <string>
using namespace std;

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

#endif // GLOABL_H

#if !defined(GLOABL_CPP)
#define GLOABL_CPP
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
#endif // GLOABL_CPP

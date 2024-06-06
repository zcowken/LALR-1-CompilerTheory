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

string& trim(string &s) 
{
	if (s.empty()) 
	{
		return s;
	}
	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
#endif // GLOABL_H

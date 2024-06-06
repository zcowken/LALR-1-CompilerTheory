#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#define BUFFER_SIZE 1024
int main()
{
    vector<vector<string>> lines;
    int row_t = 0;
    ifstream ifs("./file.txt");
    while (!ifs.eof())
    {
        char temp[BUFFER_SIZE];
        ifs.getline(temp, BUFFER_SIZE);
        stringstream ss(temp);
        // 跳过空行
        if (ss.str().empty())
        {
            continue;
        }

        lines.push_back(vector<string>());
        while (!ss.eof())
        {
            string s;
            ss >> s;
            lines[row_t].push_back(s);
        }
        row_t++;
    }
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            cout << lines[i][j] << " ";
        }
        cout << endl;
    }
}
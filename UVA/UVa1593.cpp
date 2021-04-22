#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
vector<string> Ans[1005];
string s, temp;
int max_len[1005], columns, rows;
void print(string s, int len)
{
    cout << s;
    for (int i = 0; i <= len - s.size(); i++)
        printf(" ");
}
int main()
{
    while (getline(cin, s))
    {
        stringstream io(s);
        while (io >> temp)
        {
            max_len[columns] = max(max_len[columns], (int)temp.size());
            columns++;
            Ans[rows].push_back(temp);
        }
        rows++, columns = 0;
    }
    for (int i = 0; i < rows; i++)
    {
        int j;
        for (j = 0; j < Ans[i].size() - 1; j++)
            print(Ans[i][j], max_len[j]);
        cout << Ans[i][j] << endl;
    }
    return 0;
}
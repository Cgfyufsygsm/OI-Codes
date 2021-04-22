#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
string rev(string s)
{
    int cnt0 = 0;
    reverse(s.begin(), s.end());
    for (auto i : s)
        if (i == '0')
            ++cnt0;
        else
            break;
    s.erase(s.begin(), s.begin() + cnt0);
    return (s != "" ? s : "0");
}

string deltail(string s)
{
    int cnt0 = 0;
    for (int i = s.size() - 1; i >= 0; --i)
        if (s[i] == 48)
            ++cnt0;
        else
            break;
    s.erase(s.end() - cnt0, s.end());
    return (s != "" ? s : "0");
}

int main()
{
    string s;
    cin >> s;
    if (s.back() == '%')
    {
        cout << rev(s.substr(0, s.size() - 1)) << "%" << endl;
        return 0;
    }
    for (auto i : s)
    {
        string left, right;
        if (i == '/')
        {
            left = s.substr(0, s.find("/"));
            right = s.substr(s.find("/") + 1);
            cout << rev(left) << "/" << rev(right) << endl;
            return 0;
        }
        if (i == '.')
        {
            left = s.substr(0, s.find("."));
            right = s.substr(s.find(".") + 1);
            cout << rev(left) << "." << deltail(rev(right)) << endl;
            return 0;
        }
    }
    cout << rev(s) << endl;
    return 0;
}
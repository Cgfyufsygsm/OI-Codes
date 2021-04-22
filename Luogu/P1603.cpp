#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    string str[7];
    vector<int> a;
    for (int i = 0; i < 7; i++)
        cin >> str[i];
    for (int i = 0; i < 6; i++)
    {
        transform(str[i].begin(), str[i].end(), str[i].begin(), ::tolower);
        //cout<<str[i]<<endl;
    }
    for (int i = 0; i < 6; i++)
    {
        if (str[i] == "zero")
        {
            a.push_back(0);
            continue;
        }
        if (str[i] == "one" || str[i] == "a" || str[i] == "another" || str[i] == "first")
        {
            a.push_back(1);
            continue;
        }
        if (str[i] == "two" || str[i] == "second" || str[i] == "both")
        {
            a.push_back(2);
            continue;
        }
        if (str[i] == "three" || str[i] == "third")
        {
            a.push_back(3);
            continue;
        }
        if (str[i] == "four")
        {
            a.push_back(4);
            continue;
        }
        if (str[i] == "five")
        {
            a.push_back(5);
            continue;
        }
        if (str[i] == "six")
        {
            a.push_back(6);
            continue;
        }
        if (str[i] == "seven")
        {
            a.push_back(7);
            continue;
        }
        if (str[i] == "eight")
        {
            a.push_back(8);
            continue;
        }
        if (str[i] == "nine")
        {
            a.push_back(9);
            continue;
        }
        if (str[i] == "ten")
        {
            a.push_back(10);
            continue;
        }
        if (str[i] == "eleven")
        {
            a.push_back(11);
            continue;
        }
        if (str[i] == "twelve")
        {
            a.push_back(12);
            continue;
        }
        if (str[i] == "thirteen")
        {
            a.push_back(13);
            continue;
        }
        if (str[i] == "fourteen")
        {
            a.push_back(14);
            continue;
        }
        if (str[i] == "fifteen")
        {
            a.push_back(15);
            continue;
        }
        if (str[i] == "sixteen")
        {
            a.push_back(16);
            continue;
        }
        if (str[i] == "seventeen")
        {
            a.push_back(17);
            continue;
        }
        if (str[i] == "eighteen")
        {
            a.push_back(18);
            continue;
        }
        if (str[i] == "nineteen")
        {
            a.push_back(19);
            continue;
        }
        if (str[i] == "twenty")
        {
            a.push_back(20);
            continue;
        }
    }
    if(a.empty())
    {
        cout<<0<<endl;
        return 0;
    }
    for (int i = 0; i < a.size(); i++)
        a[i] = (a[i] * a[i]) % 100;
    sort(a.begin(), a.end());
    bool flag = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == 0)
            continue;
        if (a[i] < 10 && a[i - 1] != 0)
        {
            flag = 1;
            cout << 0 << a[i];
            continue;
        }
        if (a[i] != 0)
        {
            cout << a[i];
            flag = 1;
        }
    }
    if(!flag)
        cout<<0;
    cout << endl;
    return 0;
}
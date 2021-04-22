#include <iostream>
#include <string>
#include <algorithm>
#define mian main
#define MAXN 10500
using namespace std;

bool cmp_minus(string a, string b)
{
    if (a.length() != b.length())
        return a.length() > b.length();
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] != b[i])
            return a[i] > b[i];
    }
}

string _minus(string a, string b)
{
    if(a==b) return "0";
    bool flag = cmp_minus(a, b);
    if (!flag)
        swap(a, b);
    short an[MAXN] = {0}, bn[MAXN] = {0};
    short len1 = a.length(), len2 = b.length();
    short maxl = max(len1, len2);
    for (int i = 0; i < len1; i++)
        an[i] = a[len1 - i - 1] - '0';
    for (int i = 0; i < len2; i++)
        bn[i] = b[len2 - i - 1] - '0';
    string ans1;
    int tmp = 0;
    for (int i = 0; i < maxl; i++)
    {
        tmp = an[i] - bn[i];
        if (tmp < 0)
        {
            tmp += 10;
            an[i + 1]--;
        }
        ans1=char(tmp+'0')+ans1;
    }
    short head=0;
    while(ans1[head]=='0') head++;
    string ans(ans1,head);
    if(!flag) ans="-"+ans;
    return ans;
}

int mian()
{
    string a, b;
    cin >> a >> b;
    cout << _minus(a, b);
    return 0;
}

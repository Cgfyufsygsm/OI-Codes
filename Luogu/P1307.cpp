#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
typedef long long ll;
using namespace std;
int main()
{
    ll str;
    cin>>str;
    if(str==0)
    {
        cout<<'0'<<endl;
        return 0;
    }
    bool flag=0;
    if(str<0) flag=1;
    stringstream a;
    a<<abs(str);
    string s1 = a.str();
    if(flag) cout<<'-';
    int head=s1.length()-1;
    for(head=s1.length()-1;;head--)
    {
        if(s1[head]!='0')
            break;
    }
    for(int i=head;i>=0;i--)
    {
        cout<<s1[i];
    }
    return 0;
}
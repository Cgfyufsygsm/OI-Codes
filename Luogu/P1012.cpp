#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool cmp(string a,string b)
{
    return a+b>b+a;
}
int main()
{
    int n;
    cin>>n;
    string str[n+5];
    for(int i=0;i<n;i++)
    {
        cin>>str[i];
    }
    sort(str,str+n,cmp);
    for(int i=0;i<n;i++)
    {
        cout<<str[i];
    }
    return 0;
}
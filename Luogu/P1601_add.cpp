#include <iostream>
#include <string>
#include <algorithm>
#define MAXN 10500
using namespace std;

string add(string a, string b)
{
    short an[MAXN] = {0}, bn[MAXN] = {0};
    short len1=a.length(),len2=b.length();
    short maxl=max(len1,len2);
    for (int i = 0; i<len1; i++)
        an[i] = a[len1 - 1 - i]-'0';
    for (int i = 0; i <len2; i++)
        bn[i] = b[len2 - 1 - i]-'0';
    //for(int i=0;i<MAXN;i++){cout<<an[i];}cout<<endl;
    //for(int i=0;i<MAXN;i++){cout<<bn[i];}
    int tmp1=0,tmp2=0;
    string ans;
    for(int i=0;i<maxl;i++)
    {
        tmp2=an[i]+bn[i]+tmp1;
        ans=char(tmp2%10+'0')+ans;
        tmp1=tmp2/10;
    }
    if(tmp1!=0)
        ans=char(tmp1+'0')+ans;
    return ans;

}
int main()
{
    string a,b;
    cin>>a>>b;
    cout<<add(a,b);
    return 0;
}
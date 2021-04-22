#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#define MAXN 3000
using namespace std;

string addbase(string a, string b,int base)
{
    short x[MAXN],y[MAXN];
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    int len1=a.length(),len2=b.length();
    for(int i=len1-1,j=0;i>=0;i--,j++)
        x[j]=a[i]>='A'?a[i]-'A'+10:a[i]-'0';
    for(int i=len2-1,j=0;i>=0;i--,j++)
        y[j]=b[i]>='A'?b[i]-'A'+10:b[i]-'0';
    int tmp1=0,tmp2=0;
    string ans;
    for(int i=0;i<max(len1,len2);i++)
    {
        tmp2=x[i]+y[i]+tmp1;
        ans=(char(tmp2%base)>=10?char(tmp2%base+'A'-10):char(tmp2%base+'0'))+ans;
        tmp1=tmp2/base;
    }
    if(tmp1!=0)
        ans=(char(tmp1)>=10?char(tmp1-10+'A'):char(tmp1+'0'))+ans;
    return ans;
}
int main()
{
    int base;
    cin>>base;
    string a,b;
    cin>>a>>b;
    cout<<addbase(a,b,base);
    return 0;
}
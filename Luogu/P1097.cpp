#include <map>
#include <cstdio>
#include <algorithm>
#define R register
using namespace std;

const int maxn=200000+5;
map<int,int> m;

int n,a[maxn];

inline int read()
{
    int s=0,w=1;
    R char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}

int main()
{
    int n=read();
    for(R int i=1;i<=n;i++)
    {
        a[i]=read();
        m[a[i]]++;
    }
    sort(a+1,a+n+1);
    int nn=unique(a+1,a+n+1)-(a+1);
    for(R int i=1;i<=nn;i++) printf("%d %d\n",a[i],m[a[i]]);
    return 0;
}
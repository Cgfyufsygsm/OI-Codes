#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int min(int a,int b){return a<b?a:b;}

const int maxn=105,maxl=300*105;
int L,s,t,m,pos[maxn];
int a[maxn],f[maxl];
bool vis[maxl];

int main()
{
    L=read();
    s=read(),t=read(),m=read();
    int jump=s*t;
    for(int i=1;i<=m;++i)
        pos[i]=read();
    pos[m+1]=L;
    std::sort(pos+1,pos+m+2);
    if(s==t)
    {
        int ans=0;
        for(int i=1;i<=m+1;++i)
            ans+=(pos[i]%s==0);
        printf("%d\n",ans);
        return 0;
    }
    for(int i=1;i<=m;++i)
    {
        int d=pos[i]-pos[i-1];
        if(d>=jump)d=jump;
        a[i]=a[i-1]+d;
        vis[a[i]]=1;
    }
    L=a[m]+jump;
    memset(f,0x3f,sizeof f);
    f[0]=0;
    for(int i=1;i<=L;++i)
        for(int j=s;j<=t;++j)
            if(i-j>=0)
                f[i]=min(f[i],f[i-j]+vis[i]);
    int ans=0x3f3f3f3f;
    for(int i=a[m];i<=L;++i)
        ans=min(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
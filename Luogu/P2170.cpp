#include <cstdio>
#include <cctype>
#include <cstring>

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=2e4+5;
int fa[maxn],sum[maxn],n,m,cnt;
int f[maxn];//f[i] represents if i students can be choosen 
int a[maxn];
bool vis[maxn];

int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void uni(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx!=fy)
    {
        fa[fx]=fy;
        sum[fy]+=sum[fx];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        fa[i]=i,sum[i]=1;
    int k=read();
    while(k--)
        uni(read(),read());
    for(int i=1;i<=n;i++)
    {
        if(!vis[find(i)])
        {
            a[++cnt]=sum[find(i)];
            vis[find(i)]=1;
        }
    }
    memset(f,-63,sizeof f);
    f[0]=0;
    for(int i=1;i<=cnt;i++)
        for(int j=n;j>=a[i];j--)
            f[j]=max(f[j],f[j-a[i]]+a[i]); 
    for(int i=0;m+i<=n && m-i>=0;i++)
    {
        int cur=m-i;
        if(f[cur]==cur)
        {
            printf("%d\n",f[cur]);
            return 0;
        }
        cur=m+i;
        if(f[cur]==cur)
        {
            printf("%d\n",f[cur]);
            return 0;
        }
    }
    return 0;
}
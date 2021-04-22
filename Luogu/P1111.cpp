#include <cstdio>
#include <cctype>
#include <algorithm>

using std::sort;

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

const int maxn=2005;
int n,m;
int kuai;


int fa[maxn];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void uni(int x,int y)
{
    fa[find(x)]=find(y);
    return;
}
bool ask(int x,int y)
{
    return find(x)==find(y);
}

struct edge
{
    int from,to,t;
    bool operator<(const edge &b)const
    {
        return t<b.t;
    }
}e[100000+5];

int main()
{
    kuai=n=read(),m=read();
    for(int i=1;i<=m;i++)
        e[i].from=read(),e[i].to=read(),e[i].t=read();
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(e+1,e+m+1);
    for(int i=1;i<=m;i++)
    {
        if(ask(e[i].from,e[i].to));
        else
            kuai--,uni(e[i].from,e[i].to);
        //printf("%d to %d, t=%d, kuai=%d\n",e[i].from,e[i].to,e[i].t,kuai);
        if(kuai==1)
        {
            printf("%d\n",e[i].t);
            return 0;
        }
    }
    if(kuai>1)
        printf("-1\n");
    return 0;
}
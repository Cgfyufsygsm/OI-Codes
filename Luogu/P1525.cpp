#include <cstdio>
#include <cctype>
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

using std::sort;

const int maxn=20000+5,maxm=100000+5;
int n,m;

struct hate
{
    int a,b,c;
    
}h[maxm];

bool cmp(hate a,hate b)
{
    return a.c>b.c;
}

int bin[maxn<<1];

int find(int x)
{
    return bin[x]==x?x:bin[x]=find(bin[x]);
}

bool query(int x,int y)
{
    return find(x)==find(y);
}

void uni(int x,int y)
{
    bin[find(x)]=find(y);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        h[i].a=read();
        h[i].b=read();
        h[i].c=read();
    }
    sort(h+1,h+1+m,cmp);
    for(int i=1;i<=n;i++)
        bin[i]=i,bin[i+n]=i+n;
    for(int i=1;i<=m;i++)
    {
        if(query(h[i].a,h[i].b) || query(h[i].a+n,h[i].b+n))
        {
            printf("%d\n",h[i].c);
            return 0;
        }
        uni(h[i].a,h[i].b+n);
        uni(h[i].a+n,h[i].b);
    }
    printf("0\n");
    return 0;
}
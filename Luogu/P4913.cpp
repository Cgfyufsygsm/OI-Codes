#include <cstdio>
#include <cctype>

const int maxn=1e6+5;
int n,ls[maxn],rs[maxn];
int maxstep=1;

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

void dfs(int now,int step)
{
    maxstep=maxstep>step?maxstep:step;
    if(ls[now])
        dfs(ls[now],step+1);
    if(rs[now])
        dfs(rs[now],step+1);
    return;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        ls[i]=read(),rs[i]=read();
    dfs(1,1);
    printf("%d\n",maxstep);
    return 0;
}
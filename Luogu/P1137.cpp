#include <cstdio>
#include <queue>
#include <cctype>

using namespace std;

const int maxn=100000+5;
vector<int> G[maxn];
int n,m;
int f[maxn];
int ind[maxn];

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

void ins(int x,int y)
{
    G[x].push_back(y);
    return;
}

void topo()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!ind[i])
            q.push(i),f[i]=1;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(auto i:G[now])
        {
            f[i]=max(f[i],f[now]+1);
            if(!--ind[i])
                q.push(i);
        }
    }
    return;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        ins(x,y);
        ind[y]++;
    }
    topo();
    for(int i=1;i<=n;i++)
        printf("%d\n",f[i]);
    return 0;
}
#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;

const int maxn=6e3+5;
vector<int> tree[maxn];
int r[maxn],n,fa[maxn],f[maxn][2];

inline int read()
{
    bool w=0;
    int x=0;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
            w=1;
        c=getchar();
    }
    while(isdigit(c))
        x=x*10+c-'0',c=getchar();
    return w?-x:x;
}

void dfs(int s)
{
    for(auto i:tree[s])
    {
        dfs(i);
        f[s][0]+=max(f[i][0],f[i][1]);
        f[s][1]+=f[i][0];
    }
    f[s][1]+=r[s];
    return;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        r[i]=read();
    int l,k;
    for(int i=1;i<n;i++)
    {
        l=read(),k=read();
        tree[k].push_back(l);
        fa[l]++;
    }
    int s;
    for(int i=1;i<=n;i++)
        if(!fa[i])
        {
            s=i;
            break;
        }
    dfs(s);
    printf("%d\n",max(f[s][0],f[s][1]));
    return 0;
}
#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;

const int maxn=305;
int n,m,s[maxn],f[maxn][maxn];
vector<int> son[maxn];

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

void dfs(int now)
{
    for(auto i:son[now])
    {
        dfs(i);
        for(int j=m+1;j>=1;--j)
            for(int k=1;k<j;++k)
                f[now][j]=max(f[now][j],f[now][j-k]+f[i][k]);
    }
    return;
}

int main()
{
    n=read(),m=read();
    for(int i=1,k;i<=n;i++)
    {
        k=read(),s[i]=read();
        f[i][1]=s[i];
        son[k].push_back(i);
    }
    dfs(0);
    printf("%d\n",f[0][m+1]);
    return 0;
}
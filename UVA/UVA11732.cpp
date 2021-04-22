#include <cstdio>
#include <cstring>

const int maxnode=4000*1000+555,sigma_size=26*2+10;
typedef long long ll;

inline int idx(char c)
{
    if('0'<= c && c<='9')
        return c-'0';
    else if('A'<=c && c<='Z')
        return c+10-'A';
    else if('a'<=c && c<='z')
        return c+36-'a';
}

int size;
int ch[maxnode][sigma_size];
ll end[maxnode],sum[maxnode],ans;

void insert(char *s,int v)
{
    int u=0;
    int n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=idx(s[i]);
        if(!ch[u][c])
        {
            memset(ch[size],0,sizeof ch[size]);
            sum[size]=end[size]=0;
            ch[u][c]=size++;
        }
        ++sum[u];
        u=ch[u][c];
    }
    ++end[u];
    ++sum[u];
    return;
}

void dfs(int u,int dep)
{
    ll cnt=0;
    for(int i=0;i<62;++i)
    {
        int v=ch[u][i];
        if(!v) continue;
        cnt+=sum[v]*(sum[u]-sum[v]-end[u]);
        cnt+=end[u]*sum[v]*2;
        dfs(v,dep+1);
        ch[u][i]=0;
    }
    cnt>>=1;
    ans+=cnt*((dep<<1)+1);
    ans+=(end[u]*(end[u]-1)>>1)*((dep+1)<<1);
    sum[u]=end[u]=0;
    return;
}

int main()
{
    int n;
    for(int kase=1;scanf("%d",&n) && n;++kase)
    {
        size=1;
        char tmp[1005];
        for(int i=1;i<=n;++i)
        {
            scanf("%s",tmp);
            insert(tmp,1);
        }
        ans=0;
        dfs(0,0);
        printf("Case %d: %lld\n",kase,ans);
    }
    return 0;
}
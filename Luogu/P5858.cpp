#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;
const ll maxn=5505;
ll n,w,s;
ll a[maxn],f[maxn][maxn];

inline ll read()
{
    char c = getchar();
    ll s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll max(ll a,ll b){return a>b?a:b;}
inline ll min(ll a,ll b){return a<b?a:b;}

int q[maxn];

int main()
{
    n=read(),w=read(),s=read();
    for(int i=1;i<=n;++i)
        a[i]=read();
    memset(f,0x90,sizeof f);
    f[0][0]=0;
    int head,tail,cur;
    for(int i=1;i<=n;++i)
    {
        q[head=tail=1]=cur=0;
        for(int j=1;j<=w;++j)
        {
            int low=j-1+max(0,1-j),high=min(w,j-1+min(s,w+i-j));//可供转移来的第二维下标的上下界
            for(;cur>=low && cur<=high;++cur)
            {
                while(head<=tail && f[i-1][q[tail]]<=f[i-1][cur])
                    --tail;
                q[++tail]=cur;
            }
            while(head<tail && q[head]<low)
                ++head;
            f[i][j]=max(f[i][j],f[i-1][q[head]]+j*a[i]);
        }
    }
    ll ans=f[1][0];
    for(int i=1;i<=w;++i)
        ans=max(ans,f[n][i]);
    printf("%lld\n",ans);
    return 0;
}
#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>

typedef long long ll;
const int maxn=500000+5;
int n,d,k;
int x[maxn],s[maxn];

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
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

inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}

ll f[maxn],ninf=0x8080808080808080;//当前情况下到了第i个格子最多多少分

bool chk(int mind,int maxd)
{
    f[0]=0;
    std::deque<int> q;
    int cur=0;
    for(int i=1;i<=n;++i)
    {
        for(;cur<i && x[i]-x[cur]>=mind;++cur)
        {
            while(!q.empty() && f[cur]>=f[q.back()])
                q.pop_back();
            q.push_back(cur);
        }
        while((!q.empty()) && x[i]-x[q.front()]>maxd)
            q.pop_front();
        if(q.empty())
            f[i]=ninf;
        else
            f[i]=f[q.front()]+s[i];
        if(f[i]>k)return 1;
    }
    return 0;
}

int main()
{
    n=read(),d=read(),k=read();;
    for(int i=1;i<=n;++i)
        x[i]=read(),s[i]=read();
    int l=0,r=max(d,x[n]),mid,ans=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(chk(max(1,d-mid),d+mid))
            ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
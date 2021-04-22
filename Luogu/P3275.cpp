#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>

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

const int maxn=100000+5,maxm=100000+5;
int n,k;

struct edge
{
    int to,w,next;
}e[maxm<<2];

int head[maxn],cnt;

void add(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}

bool inq[maxn];
int dis[maxn];

bool spfa(int u)
{
    inq[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to,w=e[i].w;
        if(dis[u]+w>dis[v])
        {
            dis[v]=dis[u]+w;
            if(inq[v] || !spfa(v))
                return false;
        }
    }
    inq[u]=0;
    return true;
}

int main()
{
    n=read(),k=read();
    while(k--)
    {
        int x=read(),a=read(),b=read();
        switch (x)
        {
        case 1:
            add(a,b,0);
            add(b,a,0);
            break;
        case 2:
            add(a,b,1);
            break;
        case 5:
            add(a,b,0);
            break;
        case 4:
            add(b,a,1);
            break;
        case 3:
            add(b,a,0);
            break;
        default:
            break;
        }
        if(x&1==0 && a==b)
        {
            printf("-1\n");
            return 0;
        }
    }
    for(int i=n;i>=1;i--)
        add(0,i,1);
    memset(dis,0x8f,sizeof dis);
    dis[0]=0;
    bool flag=spfa(0);
    if(!flag)
    {
        printf("-1\n");
        return 0;
    }
    long long sum=0;
    for(int i=1;i<=n;i++)
        sum+=dis[i];
    printf("%lld\n",sum);
    return 0;
}
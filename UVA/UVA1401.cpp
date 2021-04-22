#include <cstdio>
#include <cstring>

const int mod=20071027;
const int maxn=3e5+5;
const int maxnode=4000*1000+555;

char s[maxn];
int f[maxn],n;

int ch[maxnode][26];
int val[maxnode];
int size;
inline int idx(char c){return c-'a';}
void insert(char *s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=idx(s[i]);
        if(!ch[u][c])
        {
            memset(ch[size],0,sizeof ch[size]);
            val[size]=0;
            ch[u][c]=size++;
        }
        u=ch[u][c];
    }
    val[u]=v;
}

int main()
{
    int kase=0;
    while(scanf("%s",s+1)!=EOF)
    {
        n=strlen(s+1);
        memset(f,0,sizeof f);
        memset(ch[0],0,sizeof ch[0]);
        size=1;
        int tot;
        char tmp[105];
        scanf("%d",&tot);
        while(tot--)
        {
            scanf("%s",tmp);
            insert(tmp,1);
        }
        f[n+1]=1;
        for(int i=n;i>=1;--i)
        {
            int u=0;
            for(int j=i;j<=n;++j)
            {
                int c=idx(s[j]);
                if(!ch[u][c])break;
                u=ch[u][c];
                if(val[u])
                    f[i]=(f[j+1]+f[i]+mod)%mod;
            }
        }
        printf("Case %d: %d\n",++kase,f[1]);
    }
    return 0;
}
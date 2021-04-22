#include <cstdio>
#include <cctype>

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

inline int max(int a,int b)
{
    return a>b?a:b;
}

int f[10005];
const int jin=678;

void calcans(int &ans,int &t,int j)
{
    if(f[j]+1>ans)
        ans=f[j]+1,t=j+jin;
    return;
}

int main()
{
    int T=read();
    for(int kase=1;kase<=T;kase++)
    {
        int n=read(),t=read();
        int a[50];
        for(int i=1;i<=n;i++)
            a[i]=read();
        for(int i=0;i<=t;i++)
            f[i]=-1;
        f[0]=0;
        for(int i=1;i<=n;i++)
            for(int j=t-1;j>=a[i];j--)
                f[j]=max(f[j],f[j-a[i]]+1);
        int ans=-0x3f3f3f,time;
        for(int j=t-1;j>=0;j--)
            calcans(ans,time,j);
        printf("Case %d: %d %d\n",kase,ans,time);
    }
    return 0;
}
#include <cstdio>
#include <cctype>

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

inline int max(int a,int b){return a>b?a:b;}

const int maxn=1005;
int a[maxn],f[maxn],n,ans;
//f[i] 表示把 a[i] 之前经过删除能得到的使 a[i] 在 a[i] 处的最多在自己位置上面的数的个数
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    f[1]=(a[1]==1);
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(a[i]<=a[j] || a[i]>i)
                continue;
            if(i-j>=a[i]-a[j])
                f[i]=max(f[i],f[j]+1);
        }
        ans=max(ans,f[i]);
    }
    //for(int i=1;i<=n;i++)printf("%d ",f[i]);
    printf("%d\n",ans);
    return 0;
}
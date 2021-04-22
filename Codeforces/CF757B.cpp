#include <cstdio>
#include <map>

int n,v;
std::map<int,int> cnt;//存储因数对应的个数

inline int read()
{
    int s=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
    return s;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        int num=read();
        v=num>v?num:v;
        for(int j=1;j*j<=num;j++)
        {
            if(num%j==0)
            {
                cnt[j]++;
                if(num/j!=j) cnt[num/j]++;
            }
        }
    }
    int ans=1;
    for(int i=2;i<=v;i++)
    {
        //printf("%d:%d\n",i,cnt[i]);
        ans=ans>cnt[i]?ans:cnt[i];
    }
    printf("%d\n",ans);
    return 0;
}
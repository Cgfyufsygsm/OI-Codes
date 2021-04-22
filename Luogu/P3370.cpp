#include <cstdio>
#include <cstring>
#include <algorithm>

typedef unsigned long long ull;

const int maxn=10005;
const ull mod=212370440130137957ll,base=131;
char s[maxn];
ull a[maxn],n;

ull hash(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for(int i=0;i<len;i++)
        ans=(ans*base+(ull)s[i])%mod;
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        a[i]=hash(s);
    }
    std::sort(a+1,a+n+1);
    printf("%d\n",std::unique(a+1,a+n+1)-a-1);
    return 0;
}
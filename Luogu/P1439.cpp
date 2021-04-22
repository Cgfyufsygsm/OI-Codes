#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn=1e5+5;
int n,a[maxn],b[maxn],f[maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;++i)
    {
        scanf("%d",&x);
        a[x]=i;
    }
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        b[i]=a[x];
    }
    memset(f,0x7fffffff,sizeof(f));
    int len=1;
    f[1]=b[1];
    for(int i=2;i<=n;i++)
    {
        if(b[i]>f[len])
            f[++len]=b[i];
        else
        {
            int p=lower_bound(f+1,f+len+1,b[i])-f;
            f[p]=b[i];
        }
    }
    printf("%d\n",len);
    return 0;
}
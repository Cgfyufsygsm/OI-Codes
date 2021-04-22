#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using std::sort;
using std::lower_bound;

struct city
{
    int n,s;
    bool operator<(const city &b)
    {
        return n<b.n;
    }
}a[(int)2e5+5];


int f[(int)2e5+5];

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

int main()
{
    int n=read();
    for(int i=1;i<=n;i++)
        a[i].n=read(),
        a[i].s=read();
    sort(a+1,a+n+1);
    memset(f,0x7f,sizeof(f));
    int len=1;
    f[1]=a[1].s;
    for(int i=2;i<=n;i++)
    {
        if(a[i].s>=f[len])
            f[++len]=a[i].s;
        else
        {
            int p=lower_bound(f+1,f+len+1,a[i].s)-f;
            f[p]=a[i].s;
        }
    }
    printf("%d\n",len);
    return 0;
}
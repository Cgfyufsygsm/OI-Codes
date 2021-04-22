#include <cstdio>
using namespace std;
typedef unsigned long long ll;

const int maxn = 5e5 + 10;
ll ans = 0;
int a[maxn], b[maxn], n;

void msort(int l, int r)
{
    if(l==r) return;
    int mid=(l+r)/2,i=l,j=mid+1,k=l;
    msort(l,mid);msort(mid+1,r);
    while(i<=mid&&j<=r)
    {
        if(a[i]<=a[j]) b[k++]=a[i++];
        else b[k++]=a[j++],ans+=mid-i+1;
    }
    while(i<=mid) b[k++]=a[i++];
    while(j<=r) b[k++]=a[j++];
    for(int ii=l;ii<=r;ii++) a[ii]=b[ii];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1908.in", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    msort(1, n);
    printf("%llu\n", ans);
    return 0;
}
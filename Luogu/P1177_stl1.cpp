#include <cstdio>
#include <algorithm>

using namespace std;

struct cmp
{
    bool operator()(const int &a,const int &b)
    {
        return a<b;
    }
};

int a[100005];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(a+1,a+n+1,cmp());
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]);
    return 0;
}
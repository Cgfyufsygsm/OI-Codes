#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=100000+5;
int f1[maxn],f2[maxn],a[maxn],tot;

bool cmp(const int& a,const int& b)
{
    return a>b;
}

int main()
{
    memset(f1,0x7fffffff,sizeof(f1));
    memset(f2,0x7fffffff,sizeof(f2));
    while(scanf("%d",&a[++tot])!=EOF);
    f1[1]=a[1],f2[1]=a[1];
    //f[i]存储长度为i的序列的尾元素
    int len1=1,len2=1;
    for(int i=2;i<tot;i++)
    {
        if(a[i]<=f1[len1])
            f1[++len1]=a[i];
        else
        {
            int p1=upper_bound(f1+1,f1+1+len1,a[i],cmp) - f1;
            f1[p1]=a[i]; 
        }
        if(a[i]>f2[len2])
            f2[++len2]=a[i];
        else
        {
            int p2=lower_bound(f2+1,f2+len2+1,a[i])-f2;
            f2[p2]=a[i];
        }
    }
    printf("%d\n%d\n",len1,len2);
    return 0;
}
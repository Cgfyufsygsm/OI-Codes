#include <cmath>//懒得造log了就用自带的吧
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=1e6+5;
int n,k,f[21][maxn],a[maxn];

int main()
{
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&f[0][i]);
    //这里开始先造一遍最小值的
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            f[j][i]=min(f[j-1][i],f[j-1][i+(1<<(j-1))]);
    //查询，使用双指针对应左端和右端
    for(int i=1,j=k; j<=n; i++,j++)
    {
        int s=log2(j-i+1);//log2函数真香
        printf("%d ",min(f[s][i],f[s][j-(1<<s)+1]));
    }
    putchar('\n');//记得换行
    for(int j=1;j<=20;j++)//开始造最大值的，直接在上面开搞，不会出现问题，因为都会直接覆盖掉
        for(int i=1;i<=n;i++)
            f[j][i]=max(f[j-1][i],f[j-1][i+(1<<(j-1))]);
    for(int i=1,j=k; j<=n; i++,j++)
    {
        int s=log2(j-i+1);
        printf("%d ",max(f[s][i],f[s][j-(1<<s)+1]));
    }
    return 0;
}
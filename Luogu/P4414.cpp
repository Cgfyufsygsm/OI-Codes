#include <cstdio>
#include <algorithm>

int main()
{
    int a[4];
    scanf("%d %d %d\n",&a[1],&a[2],&a[3]);
    char c[4];
    scanf("%s",c+1);
    std::sort(a+1,a+4);
    for(int i=1;i<=3;i++)
        printf("%d ",a[c[i]-'A'+1]);
    return 0;
}
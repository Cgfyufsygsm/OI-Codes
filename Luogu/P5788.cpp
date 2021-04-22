#include <cstdio>

const int maxn=3e6+5;
int s[maxn],top;
int a[maxn],f[maxn],n;

int main()
{
    top=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1;i<=n;i++)
    {
        while(top&&a[s[top]]<a[i])
            f[s[top--]]=i;
        s[++top]=i;
    }
    for(int i=1;i<=n;i++)
        printf("%d ",f[i]);
    return 0;
}
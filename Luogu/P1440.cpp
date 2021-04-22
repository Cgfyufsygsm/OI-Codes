#include <cstdio>
#include <cctype>

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

const int maxn=2e6+5;
int n,m,a[maxn];
int q[maxn],p[maxn],head,tail;

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    head=1,tail=0;
    printf("0\n");
    for(int i=1;i<n;i++)
    {
        while(head<=tail && q[tail]>=a[i])
            tail--;
        q[++tail]=a[i];
        p[tail]=i;
        if(p[head]<=i-m)
            head++;
        printf("%d\n",q[head]);
    }
    return 0;
}
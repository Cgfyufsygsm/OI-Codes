#include <iostream>
#include <cstdio>
using namespace std;

int abs(int a)
{
    return a>=0?a:-a;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int a[16],b[16];
        for(int i=0;i<n;i++) scanf("%d",&a[i]);
        for(int k=1;k<=1000;k++)
        {
            for(int i=0;i<n-1;i++) b[i]=abs(a[i]-a[i+1]);
            b[n-1]=abs(a[n-1]-a[0]);
            for(int i=0;i<n;i++) a[i]=b[i];
        }
        bool flag=0;
        for(int i=0;i<n;i++) if(a[i]!=0) {flag=1;break;}
        if(flag) printf("LOOP\n");
        else printf("ZERO\n");
    }
    return 0;
}
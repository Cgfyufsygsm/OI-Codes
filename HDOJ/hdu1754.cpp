#include <bits/stdc++.h>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)
#define f(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int maxn=200000+5;

int a[maxn],f[maxn<<2];

void build(int i,int j,int k)
{
    if(i==j) f[k]=a[i];
    else
    {
        build(i,M,L);
        build(M+1,j,R);
        f[k]=max(f[L],f[R]);
    }
    return;
}

void modify(int u,int d,int i,int j,int k)
{
    if(i==j) f[k]=d;
    else
    {
        if(u<=M) modify(u,d,i,M,L);
        if(u>M) modify(u,d,M+1,j,R);
        f[k]=max(f[L],f[R]);
    }
    return;
}

int query(int u,int v,int i,int j,int k)
{
    //printf("u:%d,v:%d,i:%d,j:%d,k:%d\n",u,v,i,j,k);
    if(u==i&&v==j) return f[k];
    else
    {
        if(v<=M) return query(u,v,i,M,L);
        if(u>M) return query(u,v,M+1,j,R);
    }
    return max(query(u,M,i,M,L),query(M+1,v,M+1,j,R));
}

int main()
{
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    int n,m;
    while(cin>>n>>m)
    {
        memset(a,0,sizeof(a));
        memset(f,0,sizeof(f));
        f(i,1,n) scanf("%d",&a[i]);
        build(1,n,1);
        getchar();
        f(i,1,m)
        {
            //printf("i:%d\n",i);
            char c;int a,b;
            scanf("%c %d %d\n",&c,&a,&b);
            //printf("%c %d %d\n",c,a,b);
            if(c=='U') modify(a,b,1,n,1);
            if(c=='Q') printf("%d\n",query(a,b,1,n,1));
        }
    }
    return 0;
}
#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)

const int maxn=1e5+5;
int f[maxn<<2],tag[maxn<<2],a[maxn],n,m;

inline int read()
{
    bool w=0;
    int x=0;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
            w=1;
        c=getchar();
    }
    while(isdigit(c))
        x=x*10+c-'0',c=getchar();
    return w?-x:x;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        a[i]=read();
        f[k]=a[i]-a[i-1];
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

void down(int i,int j,int k)
{
    f[L]+=tag[k]*(M-i+1);
    f[R]+=tag[k]*(j-M);
    tag[L]+=tag[k],tag[R]+=tag[k];
    tag[k]=0;
    return;
}

void modify(int i,int j,int l,int r,int k,int d)
{
    if(i>=l && j<=r)
    {
        f[k]+=(j-i+1)*d;
        tag[k]+=d;
        return;
    }
    if(tag[k])
        down(i,j,k);
    if(l<=M)
        modify(i,M,l,r,L,d);
    if(r>M)
        modify(M+1,j,l,r,R,d);
    f[k]=f[L]+f[R];
    return;
}

int ask(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
        return f[k];
    if(tag[k])
        down(i,j,k);
    int ans=0;
    if(l<=M)
        ans+=ask(i,M,l,r,L);
    if(r>M)
        ans+=ask(M+1,j,l,r,R);
    return ans;
}


int main()
{
    n=read(),m=read();
    build(1,n,1);
    int opt,l,r,k,d,p;
    while(m--)
    {
        opt=read();
        if(opt==1)
        {
            l=read(),r=read(),k=read(),d=read();
            modify(1,n,l,l,1,k);
            if(l+1<=r)
                modify(1,n,l+1,r,1,d);
            if(r<n)
                modify(1,n,r+1,r+1,1,-((r-l)*d+k));
        }
        else
        {
            p=read();
            printf("%d\n",ask(1,n,1,p,1));
        }
    }
    return 0;
}
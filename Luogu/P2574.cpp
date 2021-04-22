#include <cstdio>
#define L (k<<1)
#define R (L|1)

const int maxn=2e5+5;
int n,m,tag[maxn<<2],f[maxn<<2];
char s[maxn];

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k]=s[i]-'0';
        return;
    }
    int m=i+j>>1;
    build(i,m,L);
    build(m+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

void down(int i,int j,int k)
{
    int m=i+j>>1;
    f[L]=m-i+1-f[L];
    f[R]=j-m-f[R];
    tag[L]=!tag[L];
    tag[R]=!tag[R];
    tag[k]=0;
    return;
}

void modify(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
    {
        f[k]=(j-i+1)-f[k];
        tag[k]=!tag[k];
        return;
    }
    if(tag[k])
        down(i,j,k);
    int m=i+j>>1;
    if(l<=m)
        modify(i,m,l,r,L);
    if(r>m)
        modify(m+1,j,l,r,R);
    f[k]=f[L]+f[R];
    return;
}

int ask(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
        return f[k];
    if(tag[k])
        down(i,j,k);
    int m=i+j>>1,ans=0;
    if(l<=m)
        ans+=ask(i,m,l,r,L);
    if(r>m)
        ans+=ask(m+1,j,l,r,R);
    return ans;
}

int main()
{
    scanf("%d %d",&n,&m);
    scanf("%s",s+1);
    build(1,n,1);
    int op,l,r;
    while(m--)
    {
        scanf("%d %d %d",&op,&l,&r);
        if(op)
            printf("%d\n",ask(1,n,l,r,1));
        else
            modify(1,n,l,r,1);
    }
    return 0;
}
#include <cstdio>
#include <cctype>

#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

inline int read()
{
    char c = getchar();
    int s = 0, x = 1;
    while (!isdigit(c))
    {
        if(c=='-')
            x=-x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

const int maxn=2e7+5,neg=1e7;
int n,f[maxn<<2];

void ins(int i,int j,int k,int x)
{
    if(i==j)
    {
        f[k]++;
        return;
    }
    if(x<=M)
        ins(i,M,L,x);
    else
        ins(M+1,j,R,x);
    f[k]=f[L]+f[R];
    return;
}

void del(int i,int j,int k,int x)
{
    if(i==j)
    {
        f[k]--;
        return;
    }
    if(x<=M)
        del(i,M,L,x);
    else
        del(M+1,j,R,x);
    f[k]=f[L]+f[R];
    return;
}

int query1(int i,int j,int x,int y,int k)
{
    if(x>y)
        return 0;
    if(x<=i && y>=j)
        return f[k];
    int ans=0;
    if(x<=M)
        ans+=query1(i,M,x,y,L);
    if(y>M)
        ans+=query1(M+1,j,x,y,R);
    return ans;
}

int query2(int i,int j,int x,int k,int cur)
{
    if(i==j)
        return i;
    if(cur+f[L]<x)
        return query2(M+1,j,x,R,cur+f[L]);
    else
        return query2(i,M,x,L,cur);
}

inline int query_rank(int x)
{
    return query1(1,maxn,1,x-1,1)+1;
}

inline int rank_query(int x)
{
    return query2(1,maxn,x,1,0);
}

inline int pre(int x)
{
    int xrank=query_rank(x);
    return rank_query(xrank-1);
}

inline int suf(int x)
{
    int xrank=query_rank(x);
    int xs=query1(1,maxn,x,x,1);
    return rank_query(xrank+xs);
}

int main()
{
    n=read();
    int opt,x;
    while(n--)
    {
        opt=read(),x=read();
        if(opt==1)
            ins(1,maxn,1,x+neg);
        else if(opt==2)
            del(1,maxn,1,x+neg);
        else if(opt==3)
            printf("%d\n",query_rank(x+neg));
        else if(opt==4)
            printf("%d\n",rank_query(x)-neg);
        else if(opt==5)
            printf("%d\n",pre(x+neg)-neg);
        else if(opt==6)
            printf("%d\n",suf(x+neg)-neg);
    }
    return 0;
}
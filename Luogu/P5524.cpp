#include <cstdio>
#include <cctype>
#include <cmath>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)
typedef long long ll;

const int maxn=2e5+5;
double fsin[maxn<<2],fcos[maxn<<2];
int n,m;
ll tag[maxn<<2];

inline ll read()
{
    char c=getchar();
    ll s=0;
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return s;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        int x=read();
        fsin[k]=sin(x);
        fcos[k]=cos(x);
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    fsin[k]=fsin[L]+fsin[R];
    fcos[k]=fcos[L]+fcos[R];
    return;
}

void down(int i,int j,int k)
{
    double lsin=fsin[L],rsin=fsin[R],lcos=fcos[L],rcos=fcos[R];
    double sine=sin(tag[k]),cosi=cos(tag[k]);
    fsin[L]=lsin*cosi+lcos*sine;
    fcos[L]=lcos*cosi-lsin*sine;
    tag[L]+=tag[k];
    fsin[R]=rsin*cosi+rcos*sine;
    fcos[R]=rcos*cosi-rsin*sine;
    tag[R]+=tag[k];
    tag[k]=0;
    return;
}

void modify(int i,int j,int l,int r,int k,int d)
{
    if(i>=l && j<=r)
    {
        double ssin=fsin[k],ccos=fcos[k];
        double sine=sin(d),cosi=cos(d);
        fsin[k]=ssin*cosi+ccos*sine;
        fcos[k]=ccos*cosi-ssin*sine;
        tag[k]+=d;
        return;
    }
    if(tag[k])
        down(i,j,k);
    if(l<=M)
        modify(i,M,l,r,L,d);
    if(r>M)
        modify(M+1,j,l,r,R,d);
    fsin[k]=fsin[L]+fsin[R];
    fcos[k]=fcos[L]+fcos[R];
    return;
}

double ask(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
        return fsin[k];
    if(tag[k])
        down(i,j,k);
    double ans=0;
    if(l<=M)
        ans+=ask(i,M,l,r,L);
    if(r>M)
        ans+=ask(M+1,j,l,r,R);
    return ans;
}

int main()
{
    n=read();
    build(1,n,1);
    m=read();
    int t,l,r,v;
    while(m--)
    {
        t=read(),l=read(),r=read();
        if(t==1)
        {
            v=read();
            modify(1,n,l,r,1,v);
        }
        else
            printf("%.1f\n",ask(1,n,l,r,1));
    }
    return 0;
}
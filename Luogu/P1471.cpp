#include <iostream>
#include <iomanip>
#include <cmath>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)
using namespace std;

const int maxn=1e5+5;
int n,m;
double f1[maxn<<2],f2[maxn<<2],tag[maxn<<2];

void build(int i,int j,int k)
{
    if(i==j)
    {
        cin>>f1[k];
        f2[k]=f1[k]*f1[k];
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f1[k]=f1[L]+f1[R];
    f2[k]=f2[L]+f2[R];
    return;
}

void down(int i,int j,int k)
{
    int l1=M-i+1,l2=j-M;
    f2[L]+=2.0*tag[k]*f1[L]+l1*tag[k]*tag[k];
    f2[R]+=2.0*tag[k]*f1[R]+l2*tag[k]*tag[k];
    f1[L]+=tag[k]*l1;
    f1[R]+=tag[k]*l2;
    tag[L]+=tag[k],tag[R]+=tag[k];
    tag[k]=0;
    return;
}

void modify(int i,int j,int l,int r,int k,double d)
{
    if(i>=l && j<=r)
    {
        f2[k]+=2.0*d*f1[k]+(j-i+1)*d*d;
        f1[k]+=(j-i+1)*d;
        tag[k]+=d;
        return;
    }
    if(tag[k])
        down(i,j,k);
    if(l<=M)
        modify(i,M,l,r,L,d);
    if(r>M)
        modify(M+1,j,l,r,R,d);
    f1[k]=f1[L]+f1[R];
    f2[k]=f2[L]+f2[R];
    return;
}

double sum1(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
        return f1[k];
    if(tag[k])
        down(i,j,k);
    double ans=0;
    if(l<=M)
        ans+=sum1(i,M,l,r,L);
    if(r>M)
        ans+=sum1(M+1,j,l,r,R);
    return ans;
}

double sum2(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
        return f2[k];
    if(tag[k])
        down(i,j,k);
    double ans=0;
    if(l<=M)
        ans+=sum2(i,M,l,r,L);
    if(r>M)
        ans+=sum2(M+1,j,l,r,R);
    return ans;
}

inline double avr(int l,int r)
{
    return sum1(1,n,l,r,1)/(r-l+1);
}

inline double fangcha(int l,int r)
{
    double avre=avr(l,r),len=r-l+1;
    return sum2(1,n,l,r,1)/len-avre*avre;
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    build(1,n,1);
    int t,x,y;
    double k;
    while(m--)
    {
        cin>>t>>x>>y;
        if(t==1)
        {
            cin>>k;
            modify(1,n,x,y,1,k);
        }
        else if(t==2)
            cout<<fixed<<setprecision(4)<<avr(x,y)<<endl;
        else
            cout<<fixed<<setprecision(4)<<fangcha(x,y)<<endl;
    }
}
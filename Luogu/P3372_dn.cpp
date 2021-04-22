#include <bits/stdc++.h>
#define L (k<<1)//进行define操作方便代码阅读
#define R (L|1)
using namespace std;
typedef long long ll;

const int maxn=1e5+5;

ll f[maxn<<2],b[maxn<<2];//f存树，b为标记，记得开4倍maxn

void build(int i,int j,int k)//造树
{
    if(i==j)
    {
        scanf("%lld",&f[k]);
        return;
    }
    int m=i+j>>1;
    build(i,m,L);
    build(m+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

void upd(int l,int r,ll d,int s,int t,int k)
{
    //[l,r]为待修改的区间，[s,t]为当前区间，d为delta，k为当前树的下标
    if(l<=s&&r>=t)//如果当前区间为待修改区间的子集
    {
        f[k]+=d*(t-s+1),b[k]+=d;//直接修改，打标记并return
        return;
    }
    int m=s+t>>1;
    if(b[k])//下放标记，如果是叶子节点就不下放
    {
        f[L]+=b[k]*(m-s+1),f[R]+=b[k]*(t-m);//先将左右儿子修改
        b[L]+=b[k],b[R]+=b[k];//然后打上标记
        b[k]=0;//最后清除掉自己的标记
    }
    if(l<=m) upd(l,r,d,s,m,L);//如果[l,r]与[s,t]的左儿子有交集，更新左半部分
    if(r>m) upd(l,r,d,m+1,t,R);//如果[l,r]与[s,t]的右儿子有交集，更新右半部分
    f[k]=f[L]+f[R];//回溯
}

ll ask(int l,int r,int s,int t,int k)
{
    //[l,r]为待查询区间，[s,t]为当前区间，k为当前节点编号
    if(l<=s&&r>=t) return f[k];//如果[s,t]是[l,r]的子集，直接return
    int m=s+t>>1;
    if(b[k])//如果有标记，先进行下放
    {
        f[L]+=b[k]*(m-s+1),f[R]+=b[k]*(t-m);
        b[L]+=b[k],b[R]+=b[k];
        b[k]=0;
    }
    ll sum=0;
    if(l<=m) sum+=ask(l,r,s,m,L);//如果[l,r]与[s,t]的左儿子有交集，查询左半部分
    if(r>m) sum+=ask(l,r,m+1,t,R);//同理，查询右半部分
    return sum;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    build(1,n,1);//TMD一定要记得建树
    for(int i=1;i<=m;i++)
    {
        int c,x,y;
        scanf("%d %d %d",&c,&x,&y);
        ll k;
        if(c==1)
        {
            scanf("%lld",&k);
            upd(x,y,k,1,n,1);
        }
        else printf("%lld\n",ask(x,y,1,n,1));
    }
    return 0;
}
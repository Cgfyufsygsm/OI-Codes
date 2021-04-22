#include <cstdio>
#include <algorithm>
#define L (k<<1)//k节点的左儿子，即k*2
#define R (L|1)//k节点的右儿子，即k*2+1
#define M (i+j>>1)//中点
using std::max;

const int maxn=1e5+5;
int a[maxn],f[maxn*4];

void upd(int k)
{
    f[k]=max(f[L],f[R]);
    return;
}

void build(int i,int j,int k)//i，j为线段的两端点
{
    if(i==j) f[k]=a[i];//如果两端重合，那f[k]就是a[i]的值
    else
    {
        build(i,M,L);//建左树
        build(M+1,j,R);//建右树
        upd(k);//建完树之后更新该节点
    }
    return;
}


int ask(int u, int v, int i, int j, int k) {
	if (u == i && v == j)
		return f[k];
	if (v <= M)
		return ask(u, v, i, M, L);
	if (u > M)
		return ask(u, v, M+1, j, R);
	return max(ask(u, M, i, M, L), ask(M+1, v, M+1, j, R));
}

inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}

int main()
{
    freopen("1.out","w",stdout);
    int n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    build(1,n,1);
    while(m--)
    {
        int l=read(),r=read();
        printf("%d\n",ask(l,r,1,n,1));
    }
    return 0;
}
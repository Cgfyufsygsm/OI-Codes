#include <cstdio>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)
#define f(i,a,b) for(int i=a;i<=b;i++)

const int maxn=5e5+5;

int a[maxn],f[maxn<<2],tag[maxn<<2];

inline int read()
{
    int s=0,w=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-') w=-w;
        c=getchar();
    }
    while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
    return s*w;
}

void build(int i,int j,int k)
{
    if(i==j) f[k]=a[i];
    else
    {
        build(i,M,L);
        build(M+1,j,R);
        f[k]=f[L]+f[R];
    }
    return;
}

void add(int u,int v,int d,int i,int j,int k)//在[u,v]上加d，i，j表示当前操作区间，k表示当前f下标
{
    //printf("u:%d v:%d d:%d i:%d j:%d k:%d\n",u,v,d,i,j,k);
    if(u==i&&v==j) {tag[k]+=d;return;}
    else if(v<=M) add(u,v,d,i,M,L);
    else if(u>M) add(u,v,d,M+1,j,R);
    else
    {
        add(u,M,d,i,M,L);
        add(M+1,v,d,M+1,j,R);
    }
    return;
}

int ask(int x,int i,int j,int k,int &tmp)
{
    tmp+=tag[k];
    if(i==j) return f[k];
    else
    {
        if(x<=M) return ask(x,i,M,L,tmp);
        if(x>M) return ask(x,M+1,j,R,tmp);
    }
}

inline void debug()
{for (int i = 1; f[i]; i++)printf("val:%d,tag:%d\n",f[i],tag[i]);}

int main()
{
    int n=read(),m=read();
    f(i,1,n) a[i]=read();
    build(1,n,1);
    
    f(i,1,m)
    {
        int type=read(),x=read();
        if(type==1)
        {
            int y=read(),k=read();
            add(x,y,k,1,n,1);
        }
        else
        {
            int tmp=0;
            printf("%d\n",ask(x,1,n,1,tmp)+tmp);
        }
    }
    return 0;
}
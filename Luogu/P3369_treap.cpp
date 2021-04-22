#include <cstdio>
#include <cctype>
#include <cstdlib>
#define L t[u].ch[0]
#define R t[u].ch[1]

inline int read()
{
    char c = getchar();
    int s = 0;bool x=0;
    while (!isdigit(c))
        x=x|(c=='-'),c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x?-s:s;
}

inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}

const int maxn=1e5+5,inf=0x3f3f3f3f;
int cnt,root;

struct treap
{
    int ch[2];
    int cnt,size;
    int val,p;
}t[maxn];

inline void maintain(int u)
{
    t[u].size=t[u].cnt+t[L].size+t[R].size;
    return;
}

void rotate(int &x,int d)//d=0把左儿子旋转上来
{
    int k=t[x].ch[d];
    t[x].ch[d]=t[k].ch[d^1];
    t[k].ch[d^1]=x;
    maintain(x);
    maintain(x=k);
}

void insert(int &u,int val)
{
    if(!u)
    {
        u=++cnt;
        t[u].size=t[u].cnt=1;
        t[u].val=val;
        t[u].p=rand();
        return;
    }
    t[u].size++;
    if(t[u].val==val)
    {
        t[u].cnt++;
        return;
    }
    int d=t[u].val<val;
    insert(t[u].ch[d],val);
    if(t[u].p>t[t[u].ch[d]].p)
        rotate(u,d);
    return;
}

void remove(int &u,int val)
{
    if(!u)return;
    if(t[u].val==val)
    {
        if(t[u].cnt>1)
        {
            t[u].cnt--;
            t[u].size--;
            return;
        }
        int d=t[L].p>t[R].p;
        if((!L)||(!R))
            u=L+R;
        else rotate(u,d),remove(u,val);
    }
    else t[u].size--,remove(t[u].ch[t[u].val<val],val);
}

int rank(int &u,int val)
{
    if(!u)return 1;
    if(t[u].val==val)
        return t[L].size+1;
    if(t[u].val>val)
        return rank(L,val);
    else return rank(R,val)+t[L].size+t[u].cnt;
}

int kth(int k)
{
    int u=root;
    while (true)
    {
        if(k<=t[L].size)
            u=L;
        else if(k>t[L].size+t[u].cnt)
            k-=t[L].size+t[u].cnt,u=R;
        else return t[u].val;
    }
}

int pre(int u,int val)
{
    if(!u)
        return -inf;
    if(t[u].val>=val)
        return pre(L,val);
    return max(pre(R,val),t[u].val);
}

int nxt(int u,int val)
{
    if(!u)
        return inf;
    if(t[u].val<=val)
        return nxt(R,val);
    return min(nxt(L,val),t[u].val);
}

int main()
{
    srand(20041031);
    int n=read();
    while(n--)
    {
        int opt=read(),x=read();
        switch(opt)
        {
            case 1:insert(root,x);break;
            case 2:remove(root,x);break;
            case 3:printf("%d\n",rank(root,x));break;
            case 4:printf("%d\n",kth(x));break;
            case 5:printf("%d\n",pre(root,x));break;
            case 6:printf("%d\n",nxt(root,x));break;
        }
    }
    return 0;
}
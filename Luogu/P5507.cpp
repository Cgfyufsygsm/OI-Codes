#include <cstdio>
#include <cctype>
#include <queue>
#define vis(x) (v[x.s[1]%4][x.s[2]%4][x.s[3]%4][x.s[4]%4][x.s[5]%4][x.s[6]%4][x.s[7]%4][x.s[8]%4][x.s[9]%4][x.s[10]%4][x.s[11]%4][x.s[12]%4])
using namespace std;

struct node
{
    int q[19];
    int s[13];
    int step;
    int chk;
};

inline void nxt(int &a)
{
    a=(a+1)%4==0?4:(a+1)%4;
    return;
}

inline int read()
{
    char c=getchar();
    int s=0;
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return s;
}

int a[13][5];
bool v[4][4][4][4][4][4][4][4][4][4][4][4];

inline int h(node &x)
{
    int ans=0;
    for(int i=1;i<=12;i++)
        ans+=x.s[i]==1?0:5-x.s[i];
    return (ans-1>>1)+1;
}

inline int check(node &x)
{
    for(int i=1;i<=12;i++)
        if(x.s[i]!=1)
            return false;
    return true;
}

bool operator>(const node &a,const node &b)
{
    return a.chk>b.chk;
}

void print(node x)
{
    for(int i=1;i<=12;i++)
        printf("%d ",x.s[i]);
    printf("\n");
}

void astar(node st)
{
    priority_queue<node,vector<node>,greater<node> > q;
    q.push(st);
    while(!q.empty())
    {
        node now=q.top();
        q.pop();
        if(check(now))
        {
            printf("%d\n",now.step);
            for(int i=1;i<=now.step;i++)
                printf("%d ",now.q[i]);
            return;
        }
        if(vis(now))
            continue;
        else
        {
            vis(now)=1;
            node nextone=now;
            for(int i=1;i<=12;i++)
            {
                nxt(nextone.s[a[i][nextone.s[i]]]);
                nxt(nextone.s[i]);
                nextone.q[++nextone.step]=i;
                nextone.chk=h(nextone)+nextone.step;
                q.push(nextone);
                nextone.s[i]=now.s[i];
                nextone.s[a[i][nextone.s[i]]]=now.s[a[i][nextone.s[i]]];
                nextone.step--;
            }
        }
    }
}

int main()
{
    node st;
    for(int i=1;i<=12;i++)
    {
        for(int j=0;j<=4;j++)
            a[i][j]=read();
        st.s[i]=a[i][0];
    }
    st.chk=h(st);
    st.step=0;
    astar(st);
    return 0;
}
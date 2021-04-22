#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

struct unionset
{
    int bin[10005];
    unionset()
    {
        for(int i=1;i<=10005;i++)
            bin[i]=i;
    }
    int anc(int x)
    {
        if(x==bin[x])
            return x;
        else return bin[x]=anc(bin[x]);
    }
    bool query(int x,int y)
    {
        return anc(x)==anc(y);
    }
    void uni(int x,int y)
    {
        bin[anc(x)]=anc(y);
    }
}u;

struct edge
{
    int from,to,dist;
    edge(){}
    edge(int _from,int _to,int _dist)
    {
        this->from=_from;
        this->to=_to;
        this->dist=_dist;
    }
};

bool cmp(edge a,edge b)
{
    return a.dist<b.dist;
}

vector<edge> q;
int n,m,s,t;

int kruskal()
{
    sort(q.begin(),q.end(),cmp);
    for(auto &e:q)
    {
        int from=e.from,to=e.to,dist=e.dist;
        if(!u.query(from,to))
            u.uni(from,to);
        if(u.query(s,t))
            return dist;
    }
}

int main()
{
    n=read(),m=read(),s=read(),t=read();
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        u=read(),v=read(),w=read();
        q.push_back(edge(u,v,w));
    }
    printf("%d\n",kruskal());
    return 0;
}
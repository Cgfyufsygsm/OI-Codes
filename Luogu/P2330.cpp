#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=305;

struct unionset
{
    int bin[maxn];
    unionset()
    {
        for(int i=1;i<=maxn;i++)
            bin[i]=i;
    }
    int anc(int x)
    {
        if(bin[x]!=x)
            return bin[x]=anc(bin[x]);
        return bin[x];
    }
    void uni(int x,int y)
    {
        bin[anc(x)]=anc(y);
    }
    bool query(int x,int y)
    {
        return anc(x)==anc(y);
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

int n,m;
vector<edge> v;

bool cmp(edge a,edge b)
{
    return a.dist<b.dist;
}

void kruskal()
{
    int _max=-0x3f3f3f3f;
    sort(v.begin(),v.end(),cmp);
    for(auto e:v)
    {
        if(!u.query(e.from,e.to))
        {
            u.uni(e.from,e.to);
            _max=max(_max,e.dist);
        }
    }
    printf("%d %d\n",n-1,_max);
    return;
}

int main()
{
    scanf("%d %d",&n,&m);
    int x,y,c;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&x,&y,&c);
        v.push_back(edge(x,y,c));
        v.push_back(edge(y,x,c));
    }
    kruskal();
    return 0;
}
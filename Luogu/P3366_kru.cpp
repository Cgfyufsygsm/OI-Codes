#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int maxn=5005;

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
        if(bin[x]==x)
            return x;
        else
            return bin[x]=anc(bin[x]);
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
set<int> s;

bool cmp(edge a,edge b)
{
    return a.dist<b.dist;
}

int kruskal()
{
    int ans=0;
    sort(v.begin(),v.end(),cmp);
    for(auto &e:v)
    {
        if(!u.query(e.from,e.to))
        {
            u.uni(e.from,e.to);
            ans+=e.dist;
            s.insert(e.from);
            s.insert(e.to);
        }
    }
    return ans;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        v.push_back(edge(x,y,z));
    }
    int ans=kruskal();
    if(s.size()!=n)
        printf("orz\n");
    else
        printf("%d\n",ans);
    return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=105;

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

int n;
vector<edge> v;

bool cmp(edge a,edge b)
{
    return a.dist<b.dist;
}

int kruskal()
{
    int ans=0;
    sort(v.begin(),v.end(),cmp);
    for(auto e:v)
    {
        if(!u.query(e.from,e.to))
        {
            u.uni(e.from,e.to);
            ans+=e.dist;
        }
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    int tmp;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&tmp);
            if(tmp)
                v.push_back(edge(i,j,tmp));
        }
    printf("%d\n",kruskal());
    return 0;
}
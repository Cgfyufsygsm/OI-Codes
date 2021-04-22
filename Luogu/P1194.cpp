#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct unionset
{
    int bin[505];
    unionset()
    {
        for(int i=1;i<=505;i++)
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

int a,b;
vector<edge> q;

int kruskal()
{
    int ans=0;
    sort(q.begin(),q.end(),cmp);
    for(auto &e:q)
    {
        int from=e.from,to=e.to,dist=e.dist;
        if(!u.query(from,to))
        {
            u.uni(from,to);
            ans+=dist;
        }
    }
    return ans;
}

int main()
{
    scanf("%d %d",&a,&b);
    for(int i=1;i<=b;i++)
    {
        for(int j=1;j<=b;j++)
        {
            int k;
            scanf("%d",&k);
            if(k&&j<=i)
                q.push_back(edge(i,j,k));
        }
    }
    int ans=kruskal();
    printf("%d\n",a+ans<a*b?a+ans:a*b);
    return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn=50050;

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
    int from,to;
    double dist;
    edge(){}
    edge(int _from,int _to,double _dist)
    {
        this->from=_from;
        this->to=_to;
        this->dist=_dist;
    }
};

double dist(int x1,int y1,int x2,int y2)//欧几里得距离
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int s,p,x[maxn],y[maxn];
vector<edge> v;

bool cmp(edge a,edge b)
{
    return a.dist<b.dist;
}

void kruskal()
{
    sort(v.begin(),v.end(),cmp);
    int cnt=0;//统计当前枚举的边的数量
    for(auto e:v)
    {
        if(!u.query(e.from,e.to))
        {
            u.uni(e.from,e.to);
            cnt++;
            if(cnt==p-s)//如果当前到了第 p-s 条边
            {
                printf("%.2f\n",e.dist);//就直接输出跑路
                return;
            }
        }
    }
}

int main()
{
    scanf("%d %d",&s,&p);
    for(int i=1;i<=p;i++)
        scanf("%d %d",x+i,y+i);
    for(int i=1;i<=p;i++)//完全图的边枚举
        for(int j=i+1;j<=p;j++)//卡常，减少循环的次数
        {
            v.push_back(edge(i,j,dist(x[i],y[i],x[j],y[j])));
            v.push_back(edge(j,i,dist(x[i],y[i],x[j],y[j])));
        }
    kruskal();
    return 0;
}
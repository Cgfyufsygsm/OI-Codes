#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
void dfs(int,int,double);
double dis[20][20]={0};
bool vis[20]={0};
int n;
struct cheese
{
    double x,y;
}c[20];
double minans=999999999.0;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>c[i].x>>c[i].y;
    }
    c[0].x=c[0].y=0;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dis[i][j]=sqrt((c[i].x-c[j].x)*(c[i].x-c[j].x)+(c[i].y-c[j].y)*(c[i].y-c[j].y));
        }
    }
    dfs(0,0,0);
    printf("%.2f",minans);
    return 0;
}
void dfs(int step,int now,double dist)
{
    if(dist>minans)
        return;
    if(step==n)
    {
        minans=(minans>dist)?dist:minans;
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            vis[i]=1;
            dfs(step+1,i,dist+dis[now][i]);
            vis[i]=0;
        }
    }
    return;
}
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <queue>
#include <set>
using namespace std;

set<int> g[27];
set<int> all;

struct node
{
    int now,step;
};

int n,m,depth;
string s;

int topo()
{
    s.clear();
    int ind[27];
    memset(ind,0,sizeof(ind));
    for(auto i:all)
        for(auto j:g[i])
            ind[j]++;
    queue<node> q;
    int visited=0;
    for(int i=1;i<=n;i++)
        if((!ind[i] && all.count(i)))
            q.push((node){i,1}),s.push_back(i+'A'-1);
    while(!q.empty())
    {
        visited++;
        int now=q.front().now,step=q.front().step;
        //printf("visited:%d, now:%c\n",visited,now+'A'-1);
        q.pop();
        int tmp=0;
        for(auto i:g[now])
        {
            ind[i]--;
            if(!ind[i])
            {
                q.push((node){i,step+1});
                s.push_back(i+'A'-1);
                depth=max(depth,step+1);
            }
        }
    }
    //printf("vis:%d\n",visited);
    if(depth==n)
        return 2;
    if(visited<all.size())
        return 0;
    return 1;
}

int main()
{
    scanf("%d %d",&n,&m);
    if(m<n-1)
    {
        printf("Sorted sequence cannot be determined.\n");
        return 0;
    }
    char c[4];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",c);
        int from=c[0]-'A'+1,to=c[2]-'A'+1;
        g[from].insert(to);
        all.insert(from),all.insert(to);
        //printf("all.size:%d\n",all.size());
        int x=topo();
        if(x==0)
        {
            printf("Inconsistency found after %d relations.\n",i);
            return 0;
        }
        if(x==2)
        {
            printf("Sorted sequence determined after %d relations: ",i);
            cout<<s<<'.'<<endl;
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.\n");
    return 0;
}
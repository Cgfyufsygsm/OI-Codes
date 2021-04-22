#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())
using namespace std;

typedef set<int> Set;
map<Set,int> IDCache;
vector<Set> SetCache;

stack<int> s;

int ID(Set x)
{
    if(IDCache.count(x)) return IDCache[x];
    SetCache.push_back(x);
    return IDCache[x]=SetCache.size()-1;
}

int main()
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        int n;
        scanf("%d",&n);
        while(n--)
        {
            string op;
            cin>>op;
            if(op[0]=='P') s.push(ID(Set()));
            else if(op[0]=='D') s.push(s.top());
            else
            {
                Set x1=SetCache[s.top()]; s.pop();
                Set x2=SetCache[s.top()]; s.pop();
                Set x;
                if(op[0]=='U') set_union(ALL(x1),ALL(x2),INS(x));
                if(op[0]=='I') set_intersection(ALL(x1),ALL(x2),INS(x));
                if(op[0]=='A')
                {
                    x=x2;
                    x.insert(ID(x1));
                }
                s.push(ID(x));
            }
            cout<<SetCache[s.top()].size()<<endl;
        }
        cout<<"***"<<endl;
    }
    return 0;
}
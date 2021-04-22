#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n;
string word[22];
int vis[21];
int ans=0;

int link(string a,string b)
{
    for(int i=1;i<min(a.size(),b.size());i++)
    {
        bool flag=1;
        for(int j=0;j<i;j++)
        if(a[a.size() - i + j] != b[j])
            flag = 0;
        if(flag)
            return i;
    }
    return 0;
}

void dfs(string now,int l)
{
    ans=max(ans,l);
    for(int i=0;i<n;i++)
    {
        if(vis[i]>=2)
            continue;
        int c=link(now,word[i]);
        if(c)
        {
            vis[i]++;
            dfs(word[i],l+word[i].size()-c);
            vis[i]--;
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=0;i<=n;i++)
        cin>>word[i];
    dfs(" "+word[n],1);
    cout<<ans<<endl;
    return 0;
}
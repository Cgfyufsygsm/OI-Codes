#include <iostream>
#include <string>
using namespace std;

void dfs(string f,string m)
{
    if(f.empty())
        return;
    //cout<<f<<' '<<m<<endl;
    int k=m.find(f[0]);
    dfs(f.substr(1,k),m.substr(0,k));
    dfs(f.substr(k+1,f.size()-k),m.substr(k+1));
    cout<<f[0];
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    string f,m;
    cin>>m>>f;
    dfs(f,m);
    return 0;
}
#include <string>
#include <iostream>
using namespace std;

void dfs(string m,string b)
{
    if(!m.size())
        return;
    cout<<b[b.size()-1];
    int k=m.find(b[b.size()-1]);
    dfs(m.substr(0,k),b.substr(0,k));
    dfs(m.substr(k+1),b.substr(k,b.size()-k-1));
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    string m,b;
    cin>>m>>b;
    dfs(m,b);
    return 0;
}
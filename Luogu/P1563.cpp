#include <iostream>
#include <string>

const int maxn=1e5+5;
int n,m;
bool face[maxn];
std::string s[maxn];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
        std::cin>>face[i]>>s[i];
    int cur=1;
    bool a;
    int b;
    for(int i=1;i<=m;i++)
    {
        std::cin>>a>>b;
        if(!a)
            b=-b;
        if(face[cur])
            b=-b;
        cur+=b;
        if(cur<1)
            cur+=n;
        if(cur>n)
            cur%=n;
    }
    std::cout<<s[cur]<<std::endl;
    return 0;
}
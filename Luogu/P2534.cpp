#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int n;
vector<int> r0,r1;//r0是从上到下的初始顺序，r1是整理过的从上到下递增的顺序
map<int,int> m1,m2;//m1存储他上面应该是什么，m2存储他下面应该是什么

int h(vector<int> rcur)
{
    int cnt=0;
    for(int i=0;i<r1.size()-1;i++)
    {
        if(m1[rcur[i]]!=rcur[i+1]&&m2[rcur[i]]!=rcur[i+1])
            cnt++;
    }
    return cnt;
}

bool iddfs(vector<int> rcur,int d,int idt)
{
    if(d+h(rcur)>idt)
        return 0;
    if(d>idt)
        return 0;
    if(rcur==r1)
        return 1;
    for(int i=2;i<=rcur.size();i++)
    {
        vector<int> tmp=rcur;
        reverse(tmp.begin(),tmp.begin()+i);
        if(iddfs(tmp,d+1,idt))
            return 1;
    }
    return 0;
}

int main()
{
    scanf("%d",&n);
    int x;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        r0.push_back(x);
    }
    r1=r0;
    sort(r1.begin(),r1.end());
    for(int i=0;i<r1.size();i++)
    {
        if(i!=0)
            m1[r1[i]]=r1[i-1];
        if(i!=r1.size()-1)
            m2[r1[i]]=r1[i+1];
    }
    for(int idt=1;idt<=2<<n;idt++)
    {
        if(iddfs(r0,0,idt))
        {
            printf("%d\n",idt);
            return 0;
        }
    }
    return 0;
}
#include <cstdio>
#include <deque>
using namespace std;

const int maxn=1e6+5;
deque<int> q;
int n,m,a[maxn];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if((!q.empty())&&q.front()<=i-m)
            q.pop_front();
        if(q.empty())
            q.push_back(i);
        else
        {
            while((!q.empty())&&a[q.back()]>=a[i])
                q.pop_back();
            q.push_back(i);
        }
        if(i>=m)
            printf("%d\n",a[q.front()]);
    }
    return 0;
}
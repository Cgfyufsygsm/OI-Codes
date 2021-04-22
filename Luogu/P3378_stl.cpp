#include <bits/stdc++.h>
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int a;
        scanf("%d",&a);
        if(a==1)
        {
            int x;
            scanf("%d",&x);
            q.push(x);
        }
        if(a==2) printf("%d\n",q.top());
        if(a==3) q.pop();
    }
    return 0;
}
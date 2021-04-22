#include <cstdio>
#include <deque>
using namespace std;

const int maxn = 1e6 + 5;
int n, k, a[maxn];
deque<int> q;

int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        while((!q.empty())&&q.front()<=i-k)
            q.pop_front();
        if (q.empty())
            q.push_back(i);
        else if (a[q.back()] >= a[i])
        {
            while ((!q.empty()) && a[q.back()] >= a[i])
                q.pop_back();
            q.push_back(i);
        }
        else
            q.push_back(i);
        if(i>=k)
            printf("%d ",a[q.front()]);
    }
    printf("\n");
    q.clear();
    for (int i = 1; i <= n; i++)
    {
        while((!q.empty())&&q.front()<=i-k)
            q.pop_front();
        if (q.empty())
            q.push_back(i);
        else if (a[q.back()] <= a[i])
        {
            while ((!q.empty()) && a[q.back()] <= a[i])
                q.pop_back();
            q.push_back(i);
        }
        else
            q.push_back(i);
        if(i>=k)
            printf("%d ",a[q.front()]);
    }
    return 0;
}
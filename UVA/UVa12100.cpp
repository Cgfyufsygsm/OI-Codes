//UVA12100 Printer Queue
#include <queue>
#include <cstdio>
using namespace std;

struct node
{
    int p;
    bool is_mine;
};

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        queue<node> q;
        priority_queue<int> q2;
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
        {
            int x;
            scanf("%d", &x);
            q.push((node){x, i == m});
            q2.push(x);
        }
        int t = 0;
        while (!q.empty())
        {
            node x = q.front();
            q.pop();
            //printf("Working on task %d, the max p is %d\n",x.p,q2.top());
            if (x.p == q2.top())
            {
                t++;
                q2.pop();
                //printf("printing\n");
                if (x.is_mine)
                    break;
                else
                    continue;
            }
            else
            {
                q.push(x);
                continue;
            }
        }
        printf("%d\n", t);
    }
    return 0;
}
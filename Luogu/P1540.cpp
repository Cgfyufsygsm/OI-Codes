#include <iostream>
#include <queue>
using namespace std;

queue<int> q;
bool inq[1010];
unsigned M, N, ans;

int main()
{
    cin >> M >> N;
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        if (inq[a])
            continue;
        else
        {
            if (q.size() >= M)
            {
                inq[q.front()] = false;
                q.pop();
            }
            q.push(a);
            inq[a] = true;
            ans++;
        }
    }
    cout << ans << endl;
}
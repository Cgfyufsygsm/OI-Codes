#include <cstdio>
#include <deque>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

struct node
{
    int x, y, dist;
    node(){}
    node(int _, int __, int ___)
    {
        x = _, y = __, dist = ___;
    }
};

const int fx[] = {0, 0, 1, -1};
const int fy[] = {1, -1, 0, 0};
const int maxn = 2005;

int n, m, sx, sy, limx, limy;
char a[maxn][maxn];
bool vis[maxn][maxn];
int ans;

std::deque<node> q;

bool chk1(int x, int y)
{
    return (!vis[x][y]) && a[x][y] == '.' && x >= 1 && x <= n && y >= 1 && y <= m;
}

int chk2(node now)
{
    int a1b = now.dist, a2b = sy - now.y;
    int a = (a1b + a2b) >> 1, b = (a1b - a2b) >> 1;
    return a <= limx && b <= limy;
}

void bfs()
{
    q.push_back(node(sx, sy, 0));
    while (!q.empty())
    {
        node now = q.front();
        int x = now.x, y = now.y, dist = now.dist;
        q.pop_front();
        if (!chk1(x, y))
            continue;
        vis[x][y] = 1;
        ans += chk2(now);
        FOR(k, 0, 3)
        {
            int xx = x + fx[k], yy = y + fy[k];
            if (fy[k])
                q.push_back(node(xx, yy, dist + 1));
            else q.push_front(node(xx, yy, dist));
        }
    }
    return;
}

int main()
{
    scanf("%d %d %d %d %d %d", &n, &m, &sx, &sy, &limx, &limy);
    FOR(i, 1, n)
        scanf("%s", a[i] + 1);
    bfs();
    printf("%d\n", ans);
    return 0;
}
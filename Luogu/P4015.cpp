#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b) {return a < b ? a : b;}

int n, s, t, _m, _n;
const int maxn = 500 + 5, maxm = 50000 + 5, inf = 1e9;
int head[maxn], cnt = 1;
int C[205][205], a[205], b[205];
int inq[maxn], dis[maxn], flow[maxn], pre[maxn];

struct edge
{
    int to, nxt, w, cost;
} e[maxm];

void add(int u, int v, int w, int c)
{
    e[++cnt].to = v, e[cnt].w = w, e[cnt].cost = c, e[cnt].nxt = head[u], head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = 0, e[cnt].cost = -c ,e[cnt].nxt = head[v], head[v] = cnt;
    return;
}

void build(int x)
{
    memset(head, 0, sizeof head), cnt = 1;
    FOR(i, 1, _m)
        add(s, i, a[i], 0);
    FOR(i, 1, _n)
        add(i + _m, t, b[i], 0);
    FOR(i, 1, _m)
        FOR(j, 1, _n)
            add(i, j + _m, inf, C[i][j] * x);
    return;
}

bool SPFA()
{
    memset(inq, 0, sizeof inq);
    memset(dis, 0x3f, sizeof dis);
    std::queue<int> q;
    q.push(s), inq[s] = 1, dis[s] = 0;
    flow[s] = inf;
    while (!q.empty())
    {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (e[i].w > 0 && e[i].cost + dis[u] < dis[v])
            {
                dis[v] = dis[u] + e[i].cost;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if (!inq[v])
                    q.push(v), inq[v] = 1;
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

int update()
{
    int now = t;
    while (now != s)
    {
        int i = pre[now];
        e[i].w -= flow[t];
        e[i ^ 1].w += flow[t];
        now = e[i ^ 1].to;
    }
    return flow[t] * dis[t];
}

int main()
{
    _m = read(), _n = read();
    n = _n + _m + 2, s = n - 1, t = n;
    FOR(i, 1, _m) a[i] = read();
    FOR(i, 1, _n) b[i] = read();
    FOR(i, 1, _m)
        FOR(j, 1, _n)
            C[i][j] = read();
    int mincost = 0;
    build(1);
    while (SPFA())
        mincost += update();
    printf("%d\n", mincost);
    mincost = 0;
    build(-1);
    while (SPFA())
        mincost += update();
    printf("%d\n", -mincost);
    return 0;
}
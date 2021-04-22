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

const int maxn = 500 + 5, maxm = 50000 + 5, inf = 1e9;
int head[maxn], cnt = 1;
int inq[maxn], dis[maxn], flow[maxn], pre[maxn];
int n, s, t;

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

int a[maxn];

int main()
{
    int _n = read();
    n = _n + 2, s = n - 1, t = n;
    int avr = 0;
    FOR(i, 1, _n)
        avr += (a[i] = read()), add(s, i, a[i], 0);
    avr /= _n;
    FOR(i, 1, _n)
    {
        add(i, t, avr, 0);
        if (i > 1)
            add(i, i - 1, inf, 1);
        if (i < _n)
            add(i, i + 1, inf, 1);
    }
    add(1, _n, inf, 1);
    add(_n, 1, inf, 1);
    int mincost = 0;
    while (SPFA())
        mincost += update();
    printf("%d\n", mincost);
    return 0;
}
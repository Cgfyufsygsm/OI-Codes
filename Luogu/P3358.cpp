#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

struct NetworkFlow
{
    static const int maxn = 2005, maxm = 10005, inf = 1e9;
    int head[maxn], cnt = 1;
    int inq[maxn], dis[maxn], flow[maxn], pre[maxn];
    int s, t;

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
        memset(dis, 0xc0, sizeof dis);
        std::queue<int> q;
        q.push(s), inq[s] = 1, dis[s] = 0;
        flow[s] = inf;
        while (!q.empty())
        {
            int u = q.front(); q.pop(); inq[u] = 0;
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (e[i].w > 0 && e[i].cost + dis[u] > dis[v])
                {
                    dis[v] = dis[u] + e[i].cost;
                    flow[v] = min(flow[u], e[i].w);
                    pre[v] = i;
                    if (!inq[v])
                        q.push(v), inq[v] = 1;
                }
            }
        }
        return dis[t] > (int)0xc0c0c0c0;
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

    int solve()
    {
        int ret = 0;
        while (SPFA())
            ret += update();
        return ret;
    }
} MCMF;

int n, k, l[505], r[505], p[1005], cntp;

int main()
{
    n = read(), k = read();
    FOR(i, 1, n)
    {
        l[i] = read(), r[i] = read();
        p[i] = l[i], p[i + n] = r[i];
    }
    std::sort(p + 1, p + n + n + 1);
    cntp = std::unique(p + 1, p + n + n + 1) - p - 1;
    MCMF.s = cntp + 1, MCMF.t = cntp + 2;
    FOR(i, 1, cntp - 1)
        MCMF.add(i, i + 1, k, 0);
    MCMF.add(MCMF.s, 1, k, 0), MCMF.add(cntp, MCMF.t, k, 0);
    FOR(i, 1, n)
        MCMF.add(std::lower_bound(p + 1, p + cntp + 1, l[i]) - p, std::lower_bound(p + 1, p + cntp + 1, r[i]) - p, 1, r[i] - l[i]);
    printf("%d\n", MCMF.solve());
    return 0;
}
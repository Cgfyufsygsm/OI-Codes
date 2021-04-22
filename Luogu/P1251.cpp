#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define int long long

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
    static const int maxn = 5005, maxm = 100005, inf = 1e18;
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
        return dis[t] < (int)0x3f3f3f3f3f3f3f3f;
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

const int maxn = 2005;
int N, r[maxn], p, m, f, n, s;

signed main()
{
    N = read();
    FOR(i, 1, N) r[i] = read();
    p = read(), m = read(), f = read(), n = read(), s = read();
    MCMF.s = N * 2 + 1, MCMF.t = MCMF.s + 1;
    FOR(i, 1, N) MCMF.add(MCMF.s, i, MCMF.inf, p), MCMF.add(MCMF.s, i + N, r[i], 0), MCMF.add(i, MCMF.t, r[i], 0);
    FOR(i, 1, N - 1) MCMF.add(i + N, i + 1 + N, MCMF.inf, 0);
    FOR(i, 1, N - 1)
    {
        if (i + m <= N)
            MCMF.add(i + N, i + m, MCMF.inf, f);
        if (i + n <= N)
            MCMF.add(i + N, i + n, MCMF.inf, s);
    }
    printf("%lld\n", MCMF.solve());
    return 0;
}
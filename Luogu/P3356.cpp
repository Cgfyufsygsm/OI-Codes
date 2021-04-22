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

struct NetworkFlow
{
    static const int maxn = 5005, maxm = 100005, inf = 1e9;
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

int r, c, n;

inline int num(int x, int y, int opt)
{
    return (x - 1) * c + y + opt * c * r;
}

int a[45][45];

void dfs(int i, int j, int cnt)
{
    if (i == r && j == c) return;
    int u = num(i, j, 1);
    for (int id = MCMF.head[u]; id; id = MCMF.e[id].nxt)
    {
        int v = MCMF.e[id].to;
        if (MCMF.e[id ^ 1].w)
        {
            if (i < r && v == num(i + 1, j, 0))
            {
                printf("%d %d\n", cnt, 0);
                --MCMF.e[id ^ 1].w;
                dfs(i + 1, j, cnt);
                return;
            }
            if (j < c && v == num(i, j + 1, 0))
            {
                printf("%d %d\n", cnt, 1);
                --MCMF.e[id ^ 1].w;
                dfs(i, j + 1, cnt);
                return;
            }
        }
    }
    return;
}

int main()
{
    n = read(), c = read(), r = read();
    FOR(i, 1, r)
        FOR(j, 1, c)
            a[i][j] = read();
    FOR(i, 1, r)
        FOR(j, 1, c)
        {
            if (j < c && a[i][j] != 1 && a[i][j + 1] != 1)
                MCMF.add(num(i, j, 1), num(i, j + 1, 0), MCMF.inf, 0);
            if (i < r && a[i][j] != 1 && a[i + 1][j] != 1)
                MCMF.add(num(i, j, 1), num(i + 1, j, 0), MCMF.inf, 0);
            if (a[i][j] != 1)
                MCMF.add(num(i, j, 0), num(i, j, 1), MCMF.inf, 0);
            if (a[i][j] == 2)
                MCMF.add(num(i, j, 0), num(i, j, 1), 1, 1);
        }
    MCMF.s = num(r, c, 1) + 1, MCMF.t = MCMF.s + 1;
    MCMF.add(MCMF.s, num(1, 1, 0), n, 0), MCMF.add(num(r, c, 1), MCMF.t, n, 0);
    MCMF.solve();
    FOR(i, 1, n)
        dfs(1, 1, i);
    return 0;
}
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

const int maxn = 5000 + 5, maxm = 4e5 + 5, inf = 1e9;
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

struct trapezoid
{
    int n, m, cnt;
    int val[25][55], num[25][55];
    void init()
    {
        m = read(), n = read(), cnt = 0;
        FOR(i, 1, n)
            FOR(j, 1, m + i - 1)
                val[i][j] = read(), num[i][j] = ++cnt;
        return;
    }
} a;

inline int in(int i, int j)
{
    return a.num[i][j];
}

inline int out(int i, int j)
{
    return a.num[i][j] + a.cnt;
}

void subtask(int t1, int t2)
{
    n = 2 + 2 * a.cnt, s = n - 1, t = n;
    memset(head, 0, sizeof head); cnt = 1;
    FOR(j, 1, a.m)
        add(s, in(1, j), 1, 0);
    FOR(j, 1, a.m + a.n - 1)
        add(out(a.n, j), t, t1, 0);
    FOR(i, 1, a.n)
        FOR(j, 1, i + a.m - 1)
            add(in(i, j), out(i, j), t1, a.val[i][j]);
    FOR(i, 1, a.n - 1)
        FOR(j, 1, i + a.m - 1)
            add(out(i, j), in(i + 1, j), t2, 0), add(out(i, j), in(i + 1, j + 1), t2, 0);
    int ans = 0;
    while (SPFA())
        ans += update();
    printf("%d\n", ans);
    return;
}

int main()
{
    a.init();
    subtask(1, 1);
    subtask(inf, 1);
    subtask(inf, inf);
    return 0;
}
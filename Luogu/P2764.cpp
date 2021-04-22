#include <cstdio>
#include <cctype>
#include <cstring>
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

const int maxn = 500 + 5, maxm = 50000 + 5;

int n, s, t;
int head[maxn], cnt = 1;
int cur[maxn], dep[maxn];

struct edge
{
    int to, w, nxt;
} e[maxm];

void add(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].w = 0;
    e[cnt].nxt = head[v];
    head[v] = cnt;
    return;
}

int q[maxn], qhead, qtail;

bool bfs()
{
    FOR(i, 0, n)
        dep[i] = -1, cur[i] = head[i];
    q[qhead = qtail = 1] = s;
    dep[s] = 0;
    while (qhead <= qtail)
    {
        int u = q[qhead++];
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (dep[v] == -1 && e[i].w > 0)
            {
                q[++qtail] = v;
                dep[v] = dep[u] + 1;
                if (v == t)
                    return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int in)
{
    if (u == t)
        return in;
    int out = 0;
    for (int i = cur[u]; i; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].to;
        if (dep[v] == dep[u] + 1 && e[i].w)
        {
            int res = dfs(v, min(in, e[i].w));
            e[i].w -= res;
            e[i ^ 1].w += res;
            in -= res;
            out += res;
        }
        if (!in) break;
    }
    if (!out)
        dep[u] = -1;
    return out;
}

int dinic()
{
    int ret = 0;
    while (bfs())
        ret += dfs(s, 1e9);
    return ret;
}

bool vis[maxn];

int main()
{
    int _n = read(), _m = read();
    n = _n * 2 + 2, s = n - 1, t = n;
    FOR(i, 1, _n)
        add(s, i, 1), add(i + _n, t, 1);
    FOR(i, 1, _m)
    {
        int u = read(), v = read();
        add(u, v + _n, 1);
    }
    int ans = _n - dinic();
    FOR(st, 1, _n)
    {
        int u = st;
        if (vis[st]) continue;
        bool flag = 1;
        while (flag)
        {
            flag = 0;
            printf("%d ", u);
            vis[u] = 1;
            for (int i = head[u]; i; i = e[i].nxt)
                if (e[i].to - _n >= 1 && e[i].to - _n <= _n && !e[i].w)
                {
                    u = e[i].to - _n;
                    flag = 1;
                    break;
                }
        }
        printf("\n");
    }
    printf("%d\n", ans);
    return 0;
}
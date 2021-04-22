#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 2000 + 5;

int head[maxn], cnt = 1;

struct edge
{
    int to, nxt, w;
} e[maxn << 1];

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
    //printf("added %d to %d of %d\n", u, v, w);
    return;
}

int x[maxn], f[maxn], n, s, t;
int cur[maxn], dep[maxn];

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

int main()
{
    int _n = read(), ans1 = 0;
    if (_n == 1)
    {
        printf("1\n1\n1\n");
        return 0;
    }
    FOR(i, 1, _n)
    {
        x[i] = read(), f[i] = 1;
        FOR(j, 1, i - 1)
            if (x[j] <= x[i])
                f[i] = max(f[j] + 1, f[i]);
        ans1 = max(ans1, f[i]);
    }
    printf("%d\n", ans1);
    n = 2 * _n + 2, s = n - 1, t = n;
    FOR(i, 1, _n)
    {
        if (f[i] == 1)
            add(s, i, 1);
        add(i, _n + i, 1);
        if (f[i] == ans1)
            add(_n + i, t, 1);
    }
    FOR(i, 1, _n)
        FOR(j, 1, i - 1)
            if (x[i] >= x[j] && f[i] == f[j] + 1)
                add(j + _n, i, 1);
    printf("%d\n", dinic());
    cnt = 1; memset(head, 0, sizeof head);
    FOR(i, 1, _n)
    {
        if (f[i] == 1)
            add(s, i, (i == 1) ? 1e8 : 1);
        add(i, _n + i, (i == 1 || i == _n) ? 1e8 : 1);
        if (f[i] == ans1)
            add(_n + i, t, (i == _n) ? 1e8 : 1);
    }
    FOR(i, 1, _n)
        FOR(j, 1, i - 1)
            if (x[i] >= x[j] && f[i] == f[j] + 1)
                add(j + _n, i, 1);
    printf("%d\n", dinic());
    return 0;
}
#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b) {return a < b ? a : b;}
inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 305, maxm = 505;

struct software
{
    int w, v, d;
} a[maxn];

int n, m;

struct Graph
{
    int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
    void add(int u, int v)
    {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
        return;
    }
} g0, g;

int dfn[maxn], low[maxn], dfnClock, bel[maxn], sccCnt, deg[maxn];
int stk[maxn], top, vis[maxn];
int w[maxn], v[maxn], f[maxn][maxm];// weight, value;

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u, vis[u] = 1;
    for (int i = g0.head[u]; i; i = g0.nxt[i])
    {
        int v = g0.to[i];
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++sccCnt;
        int v;
        do
        {
            bel[v = stk[top--]] = sccCnt;
            vis[v] = 0;
        } while (v != u);
    }
    return;
}

void dfs(int u)
{
    FOR(i, w[u], m)
        f[u][i] = v[u];
    for (int i = g.head[u]; i; i = g.nxt[i])
    {
        int v = g.to[i];
        dfs(v);
        for (int j = m - w[u]; j >= 0; --j)
            for (int k = 0; k <= j; ++k)
                f[u][j + w[u]] = max(f[u][j + w[u]], f[u][j + w[u] - k] + f[v][k]);
    }
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
        a[i].w = read();
    FOR(i, 1, n)
        a[i].v = read();
    FOR(i, 1, n)
    {
        a[i].d = read();
        g0.add(a[i].d, i);
    }
    FOR(i, 0, n)
        if (!dfn[i])
            tarjan(i);
    FOR(u, 0, n)
    {
        w[bel[u]] += a[u].w, v[bel[u]] += a[u].v;
        for (int i = g0.head[u]; i; i = g0.nxt[i])
        {
            int v = g0.to[i];
            if (bel[v] != bel[u])
                g.add(bel[u], bel[v]), ++deg[bel[v]];
        }
    }
    FOR(u, 1, sccCnt)
        if (!deg[u] && u != bel[0])
            g.add(bel[0], u);
    dfs(bel[0]);
    int ans = -1;
    FOR(i, 0, m)
        ans = max(ans, f[bel[0]][i]);
    printf("%d\n", ans);
    return 0;
}
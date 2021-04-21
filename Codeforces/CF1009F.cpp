#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5;

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

int n;
int head[maxn], to[maxn << 1], nxt[maxn << 1], tot;

inline void add(int u, int v)
{
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
    return;
}

int h[maxn], son[maxn], top[maxn], ans[maxn];
int buf[maxn], *f[maxn], *now = buf;

void dfs1(int u, int fa)
{
    h[u] = -1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        if (h[v] > h[u]) h[u] = h[v], son[u] = v;
    }
    ++h[u];
    if (!son[u]) h[u] = 1;
    return;
}

void dfs2(int u, int fa)
{
    f[u][0] = 1;
    if (son[u])
    {
        f[son[u]] = f[u] + 1;
        dfs2(son[u], u);
        ans[u] = ans[son[u]] + 1;
    }
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa || v == son[u]) continue;
        f[v] = now, now += h[v];
        dfs2(v, u);
        FOR(j, 1, h[v])
        {
            f[u][j] += f[v][j - 1];
            if (f[u][j] > f[u][ans[u]] || (f[u][j] == f[u][ans[u]] && j < ans[u]))
                ans[u] = j;
        }
    }
    if (f[u][ans[u]] == 1) ans[u] = 0;
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs1(1, 0);
    f[1] = now, now += h[1];
    dfs2(1, 0);
    FOR(i, 1, n)
        printf("%d\n", ans[i]);
    return 0;
}
#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 5e3 + 5;

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

typedef long long ll;

inline int max(int a, int b) {return a > b ? a : b;}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
int n;
ll *f[maxn], *g[maxn], buff[maxn * 10], bufg[maxn * 10], *nowf = buff, *nowg = bufg, ans;
int h[maxn], son[maxn], dep[maxn];

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa)
            dfs1(v, u);
        if (h[v] > h[son[u]])
            son[u] = v;
    }
    h[u] = h[son[u]] + 1;
    return;
}

void dfs2(int u, int fa)
{
    if (son[u])
        f[son[u]] = f[u] + 1, g[son[u]] = g[u] - 1, dfs2(son[u], u);
    f[u][0] = 1, ans += g[u][0];
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa || v == son[u]) continue;
        f[v] = nowf, nowf += h[v];
        nowg += (h[v] << 1) + 5, g[v] = nowg++;
        dfs2(v, u);
        FOR(i, 0, h[v] - 1)
        {
            if (i) ans += f[u][i - 1] * g[v][i];
            ans += g[u][i + 1] * f[v][i];
        }
        FOR(i, 0, h[v] - 1)
        {
            g[u][i + 1] += f[u][i + 1] * f[v][i];
            if (i) g[u][i - 1] += g[v][i];
            f[u][i + 1] += f[v][i];
        }
    }
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    f[1] = nowf, nowf += h[1], nowg += (h[1] << 1) + 5, g[1] = nowg++;
    dfs2(1, 0);
    printf("%lld\n", ans);
    return 0;
}
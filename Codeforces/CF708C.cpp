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

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 400000 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
int n, size[maxn], maxson[maxn];
int f[maxn][2], g[maxn], ans[maxn], pos[maxn];

void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs1(int u, int fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[maxson[u]])
            maxson[u] = v;
        int tmp = 0;
        if (size[v] <= n / 2)
            tmp = size[v];
        else tmp = f[v][0];
        if (tmp > f[u][0])
            f[u][1] = f[u][0], f[u][0] = tmp, pos[u] = v;
        else if (tmp > f[u][1])
            f[u][1] = tmp;
    }
    return;
}

void dfs2(int u, int fa)
{
    ans[u] = 1;
    if (size[maxson[u]] > n / 2)
        ans[u] = size[maxson[u]] - f[maxson[u]][0] <= n / 2;
    else if (n - size[u] > n / 2)
        ans[u] = (n - size[u] - g[u] <= n / 2);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        int tmp;
        if (n - size[u] > n / 2)
            tmp = g[u];
        else tmp = n - size[u];
        g[v] = max(g[v], tmp);
        if (v == pos[u])
            g[v] = max(g[v], f[u][1]);
        else g[v] = max(g[v], f[u][0]);
        dfs2(v, u);
    }
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
    dfs2(1, 0);
    FOR(i, 1, n) printf("%d ", ans[i]);
    return 0;
}
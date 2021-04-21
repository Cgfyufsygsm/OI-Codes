#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5;

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

int n, c[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
int son[maxn], size[maxn], fa[maxn];

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs1(int u, int father)
{
    size[u] = 1, fa[u] = father;
    int maxson = -1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == father) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > maxson)
            maxson = size[v], son[u] = v;
    }
    return;
}

int vis[maxn], ans[maxn], flag, tmp;

void calc(int u, int val)
{
    if (val > 0)
    {
        if (!vis[c[u]])
            ++tmp;
        ++vis[c[u]];
    }
    else
    {
        if (vis[c[u]] <= 1)
            --tmp;
        --vis[c[u]];
    }
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != fa[u] && to[i] != flag)
            calc(to[i], val);
    return;
}

void dfs2(int u, int keep)
{
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != fa[u] && to[i] != son[u])
            dfs2(to[i], 0);
    if (son[u]) dfs2(son[u], 1), flag = son[u];
    calc(u, 1);
    flag = 0;
    ans[u] = tmp;
    if (!keep) calc(u, -1);
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
    FOR(i, 1, n) c[i] = read();
    dfs1(1, 0);
    dfs2(1, 0);
    int m = read();
    while (m--)
        printf("%d\n", ans[read()]);
    return 0;
}
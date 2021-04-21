#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 200000 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int n, e[maxn];

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int dis[maxn], p1, p2, vis[maxn];

void dfs1(int u, int fa, int &p)
{
    if (dis[u] > dis[p]) p = u;
    GO(u)
    {
        if (v == fa) continue;
        dis[v] = dis[u] + 1;
        dfs1(v, u, p);
    }
    return;
}

bool dfs2(int u, int fa)
{
    if (u == p2)
    {
        vis[u] = 1;
        return 1;
    }
    GO(u)
    {
        if (v == fa) continue;
        if (dfs2(v, u))
        {
            vis[u] = 1;
            return 1;
        }
    }
    return 0;
}

int cnt = 0;

void dfs3(int u, int fa)
{
    e[u] = ++cnt;
    GO(u)
    {
        if (vis[v] || v == fa) continue;
        dfs3(v, u);
    }
    GO(u)
    {
        if (v == fa) continue;
        if (vis[v])
        {
            dfs3(v, u);
            return;
        }
    }
    ++cnt;
}

int main()
{
    n = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs1(1, 0, p1);
    dis[p1] = 0;
    dfs1(p1, 0, p2);
    dfs2(p1, 0);
    dfs3(p1, 0);
    FOR(i, 1, n) printf("%d ", e[i]);
    return 0;
}
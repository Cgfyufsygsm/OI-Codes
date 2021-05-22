#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 2e5 + 5;

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
int head[maxn], to[maxn], nxt[maxn], cnte;
int dep[maxn], h[maxn], son[maxn];
int buf[maxn << 1], *f[maxn], *now = buf;

struct node
{
    int id, d;
    node() {}
    node(int i, int de) {id = i, d = de;}
};

int ans[maxn];

std::vector<node> query[maxn];

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs1(int u, int d)
{
    h[u] = 1;
    dep[u] = d;
    GO(u)
    {
        dfs1(v, d + 1);
        if (h[v] > h[son[u]]) son[u] = v, h[u] = h[v] + 1;
    }
    return;
}

void dfs2(int u)
{
    f[u][0] = 1;
    if (son[u])
    {
        f[son[u]] = f[u] + 1;
        dfs2(son[u]);
    }
    GO(u)
    {
        if (v == son[u]) continue;
        f[v] = now, now += h[v];
        dfs2(v);
        FOR(j, 1, h[v])
            f[u][j] += f[v][j - 1];
    }
    FOR(i, 0, (int)query[u].size() - 1)
        ans[query[u][i].id] = f[u][query[u][i].d];
    return;
}

int main()
{
    n = read();
    FOR(i, 2, n)
    {
        int f = read();
        add(f, i);
    }
    dfs1(1, 1);
    f[1] = now, now += h[1];
    int q = read();
    FOR(i, 1, q)
    {
        int u = read(), d = read();
        d -= dep[u] - 1;
        if (d < h[u] && d >= 0)
            query[u].push_back(node(i, d));
        else ans[i] = 0;
    }
    dfs2(1);
    FOR(i, 1, q) printf("%d\n", ans[i]);
    return 0;
}
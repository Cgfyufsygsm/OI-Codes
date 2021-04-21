#include <cstdio>
#include <cctype>
#include <vector>
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

struct node
{
    int id, k;
};

std::vector<node> query[maxn];
int n, fa[maxn];
int head[maxn], to[maxn], nxt[maxn], cnt;
int h[maxn], son[maxn], ans[maxn];
int *f[maxn], buf[maxn << 1], *now = buf;

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int stk[maxn], top;

void dfs1(int u)
{
    stk[++top] = u;
    FOR(i, 0, (int)query[u].size() - 1)
        if (query[u][i].k < top && query[u][i].k)
            query[stk[top - query[u][i].k]].push_back(query[u][i]);
    query[u].resize(0);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        dfs1(v);
        if (h[v] > h[son[u]]) son[u] = v;
    }
    h[u] = h[son[u]] + 1;
    --top;
    return;
}

void dfs2(int u)
{
    f[u][0] = 1;
    if (son[u]) f[son[u]] = f[u] + 1, dfs2(son[u]);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == son[u]) continue;
        f[v] = now, now += h[v];
        dfs2(v);
        FOR(i, 1, h[v])
            f[u][i] += f[v][i - 1];
    }
    FOR(i, 0, (int)query[u].size() - 1)
        ans[query[u][i].id] = f[u][query[u][i].k] - 1;
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n)
    {
        fa[i] = read();
        if (fa[i]) add(fa[i], i);
    }
    int q = read();
    FOR(i, 1, q)
    {
        int u = read(), k = read();
        query[u].push_back((node){i, k});
    }
    FOR(u, 1, n)
        if (!fa[u])
            dfs1(u), f[u] = now, now += h[u], dfs2(u);
    FOR(i, 1, q)
        printf("%d ", ans[i]);
    return 0;
}
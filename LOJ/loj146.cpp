#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
#define lowbit(x) (x & -x)

namespace fastIO
{
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
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
}

using namespace fastIO;

const int maxn = 1e6 + 5;
typedef long long ll;

int n, m, root;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int fa[maxn], son[maxn], size[maxn], dep[maxn], top[maxn];
int dfn[maxn], low[maxn], cntdfn;
ll sum[maxn];

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

ll val[maxn];

void dfs1(int u, int f)
{
    sum[u] = val[u];
    dep[u] = dep[f] + 1, fa[u] = f, size[u] = 1;
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v], sum[u] += sum[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf)
{
    dfn[u] = ++cntdfn;
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    GO(u)
    {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    low[u] = cntdfn;
    return;
}

int getLCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct BIT
{
    ll f[maxn];

    void modify(int x, ll v)
    {
        for (; x <= cntdfn; x += lowbit(x))
            f[x] += v;
        return;
    }

    ll sum(int x)
    {
        ll ret = 0;
        for (; x; x -= lowbit(x))
            ret += f[x];
        return ret;
    }
    il ll sum(int x, int y) {return sum(y) - sum(x - 1);}
} bit1, bit2;

int main()
{
    n = read(), m = read(), root = read();
    FOR(i, 1, n) val[i] = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs1(root, 0);
    dfs2(root, root);
    while (m--)
    {
        int op = read(), u = read();
        if (op == 1)
        {
            int v = read(), d = read(), lca = getLCA(u, v);
            bit1.modify(dfn[u], d), bit1.modify(dfn[v], d);
            bit2.modify(dfn[u], 1ll * dep[u] * d), bit2.modify(dfn[v], 1ll * dep[v] * d);
            bit1.modify(dfn[lca], -d);
            bit2.modify(dfn[lca], 1ll * dep[lca] * (-d));
            if (fa[lca]) bit1.modify(dfn[fa[lca]], -d), bit2.modify(dfn[fa[lca]], 1ll * dep[fa[lca]] * (-d));
        }
        else if (op == 2)
            printf("%lld\n", bit1.sum(dfn[u], low[u]) + val[u]);
        else if (op == 3)
            printf("%lld\n", bit2.sum(dfn[u], low[u]) - (dep[u] - 1) * bit1.sum(dfn[u], low[u]) + sum[u]);
    }
    return 0;
}
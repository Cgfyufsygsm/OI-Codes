#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
#define lowbit(x) (x & -x)

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

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

typedef long long ll;
const int maxn = 1e6 + 5;

int n, m, root;
ll val[maxn], sum[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int dep[maxn], fa[maxn], top[maxn], size[maxn], son[maxn];
int dfn[maxn], cntdfn, low[maxn];

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

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs1(int u, int f)
{
    fa[u] = f, size[u] = 1, dep[u] = dep[f] + 1;
    sum[u] = val[u] + sum[f];
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[u] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf)
{
    top[u] = topf, dfn[u] = ++cntdfn;
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

ll query(int u)
{
    if (!u) return 0;
    return sum[u] + bit1.sum(dfn[u]) + bit2.sum(dfn[u]) * (dep[u] + 1);
}

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
        int op = read(), a = read(), b = read();
        if (op == 1)
            bit1.modify(dfn[a], b), bit1.modify(low[a] + 1, -b);
        else if (op == 2)
            bit1.modify(dfn[a], 1ll * (-b) * dep[a]), bit1.modify(low[a] + 1, 1ll * b * dep[a]),
            bit2.modify(dfn[a], b), bit2.modify(low[a] + 1, -b);
        else
        {
            int lca = getLCA(a, b);
            printf("%lld\n", query(a) + query(b) - query(lca) - query(fa[lca]));
        }
    }
    return 0;
}
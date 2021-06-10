#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 1e5 + 5, maxm = 5e6 + 5;

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

il int max(int a, int b) {return a > b ? a : b;}

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int fa[maxn], dep[maxn], top[maxn], son[maxn], size[maxn];

void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1, size[u] = 1;
    GO(u)
    {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf)
{
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    GO(u)
    {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int LCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int n, m;
int X[maxn], Y[maxn], Z[maxn], maxz;
int root[maxn], cnt;

struct node
{
    int ls, rs, val, ans;
} t[maxm];

#define L t[k].ls
#define R t[k].rs
#define M ((i + j) >> 1)

il void pushup(int k)
{
    if (t[L].val >= t[R].val) t[k].val = t[L].val, t[k].ans = t[L].ans;
    else t[k].val = t[R].val, t[k].ans = t[R].ans;
    return;
}

int modify(int k, int i, int j, int pos, int val)
{
    if (!k) k = ++cnt;
    if (i == j)
    {
        t[k].val += val;
        t[k].ans = pos;
        return k;
    }
    if (pos <= M) t[k].ls = modify(L, i, M, pos, val);
    else t[k].rs = modify(R, M + 1, j, pos, val);
    pushup(k);
    return k;
}

int merge(int k1, int k2, int i, int j)
{
    if (!k1 || !k2) return k1 + k2;
    if (i == j)
    {
        t[k1].val += t[k2].val;
        t[k1].ans = i;
        return k1;
    }
    t[k1].ls = merge(t[k1].ls, t[k2].ls, i, M);
    t[k1].rs = merge(t[k1].rs, t[k2].rs, M + 1, j);
    pushup(k1);
    return k1;
}

int ans[maxn];

void dfs3(int u)
{
    GO(u)
    {
        if (v == fa[u]) continue;
        dfs3(v);
        root[u] = merge(root[u], root[v], 1, maxz);
    }
    if (t[root[u]].val) ans[u] = t[root[u]].ans;
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n - 1)
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }
    dfs1(1, 0), dfs2(1, 1);
    FOR(i, 1, m) X[i] = read(), Y[i] = read(), Z[i] = read(), maxz = max(maxz, Z[i]);
    FOR(i, 1, m)
    {
        int lca = LCA(X[i], Y[i]);
        root[X[i]] = modify(root[X[i]], 1, maxz, Z[i], 1);
        root[Y[i]] = modify(root[Y[i]], 1, maxz, Z[i], 1);
        root[lca] = modify(root[lca], 1, maxz, Z[i], -1);
        if (fa[lca]) root[fa[lca]] = modify(root[fa[lca]], 1, maxz, Z[i], -1);
    }
    dfs3(1);
    FOR(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
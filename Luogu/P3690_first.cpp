#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define il inline

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

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 5;

int n, m;

int ch[maxn][2], f[maxn], size[maxn], tag[maxn], val[maxn], res[maxn];
#define ls(u) ch[u][0]
#define rs(u) ch[u][1]

il void pushup(int u)
{
    size[u] = size[ls(u)] + size[rs(u)] + 1;
    res[u] = res[ls(u)] ^ res[rs(u)] ^ val[u];
    return;
}

il void pushdown(int u)
{
    if (tag[u])
    {
        if (ls(u)) tag[ls(u)] ^= 1, swap(ls(ls(u)), rs(ls(u)));
        if (rs(u)) tag[rs(u)] ^= 1, swap(ls(rs(u)), rs(rs(u)));
        tag[u] ^= 1;
    }
    return;
}

#define get(u) (ch[f[u]][1] == u)
#define isroot(u) (ch[f[u]][0] != u && ch[f[u]][1] != u)

il void pushall(int u)
{
    if (!isroot(u)) pushall(f[u]);
    pushdown(u);
    return;
}

il void rotate(int u)
{
    int fa = f[u], gfa = f[fa], k1 = get(u), k2 = get(fa);
    if (!isroot(fa)) ch[gfa][k2] = u;
    ch[fa][k1] = ch[u][k1 ^ 1], f[ch[u][k1 ^ 1]] = fa;
    ch[u][k1 ^ 1] = fa, f[fa] = u, f[u] = gfa;
    pushup(fa), pushup(u);
    return;
}

il void splay(int u)
{
    pushall(u);
    for (int fa; fa = f[u], !isroot(u); rotate(u))
    {
        if (!isroot(fa))
            rotate(get(fa) == get(u) ? fa : u);
    }
    return;
}

il int access(int u)
{
    int p;
    for (p = 0; u; p = u, u = f[u])
        splay(u), ch[u][1] = p, pushup(u);
    return p;
}

il void makeroot(int u)
{
    u = access(u);
    swap(ls(u), rs(u));
    tag[u] ^= 1;
    return;
}

il int findroot(int u)
{
    access(u), splay(u);
    while (ls(u)) pushdown(u), u = ls(u);
    splay(u);
    return u;
}

il void link(int u, int v)
{
    makeroot(u);
    if (findroot(v) == u) return;
    splay(u);
    f[u] = v;
    return;
}

il void cut(int u, int v)
{
    makeroot(u);
    if (findroot(v) != u || f[v] != u || ch[v][0]) return;
    f[v] = ch[u][1] = 0;
    pushall(u);
    return;
}

il void split(int u, int v)
{
    makeroot(u);
    access(v);
    splay(v);
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
        val[i] = read();
    while (m--)
    {
        int opt = read(), x = read(), y = read();
        if (opt == 0)
            split(x, y), printf("%d\n", res[y]);
        else if (opt == 1)
            link(x, y);
        else if (opt == 2)
            cut(x, y);
        else if (opt == 3)
            splay(x), val[x] = y, pushup(x);
    }
    return 0;
}
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

struct Node
{
    int ch[2], fa, size, tag, val, res;
} t[maxn];


#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

il void pushUp(int u)
{
    t[u].size = t[ls(u)].size + t[rs(u)].size + 1;
    t[u].res = t[ls(u)].res ^ t[rs(u)].res ^ t[u].val;
    return;
}

il void pushDown(int u)
{
    if (t[u].tag)
    {
        if (ls(u)) t[ls(u)].tag ^= 1, swap(ls(ls(u)), rs(ls(u)));
        if (rs(u)) t[rs(u)].tag ^= 1, swap(ls(rs(u)), rs(rs(u)));
        t[u].tag ^= 1;
    }
    return;
}

#define get(u) (rs(t[u].fa) == u)
#define isRoot(u) (ls(t[u].fa) != u && rs(t[u].fa) != u)

il void pushAll(int u)
{
    if (!isRoot(u)) pushAll(t[u].fa);
    pushDown(u);
    return;
}

il void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa, k1 = get(u), k2 = get(fa);
    if (!isRoot(fa)) t[gfa].ch[k2] = u;
    t[fa].ch[k1] = t[u].ch[k1 ^ 1], t[t[u].ch[k1 ^ 1]].fa = fa;
    t[u].fa = gfa, t[fa].fa = u, t[u].ch[k1 ^ 1] = fa;
    pushUp(fa), pushUp(u);
    return;
}

il void splay(int u)
{
    pushAll(u);
    for (int fa; fa = t[u].fa, !isRoot(u); rotate(u))
    {
        if (!isRoot(fa))
            rotate(get(fa) == get(u) ? fa : u);
    }
    return;
}

il int access(int u)
{
    int p;
    for (p = 0; u; p = u, u = t[u].fa)
        splay(u), rs(u) = p, pushUp(u);
    return p;
}

il void makeRoot(int u)
{
    u = access(u);
    swap(ls(u), rs(u));
    t[u].tag ^= 1;
    return;
}

il int findRoot(int u)
{
    access(u), splay(u);
    while (ls(u)) pushDown(u), u = ls(u);
    splay(u);
    return u;
}

il void link(int u, int v)
{
    makeRoot(u);
    if (findRoot(v) == u) return;
    splay(u);
    t[u].fa = v;
    return;
}

il void cut(int u, int v)
{
    makeRoot(u);
    access(v);
    splay(u);
    if (rs(u) != v || rs(v)) return;
    t[v].fa = rs(u) = 0;
    pushUp(u);
    return;
}

il void split(int u, int v)
{
    makeRoot(u);
    access(v);
    splay(v);
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n)
        t[i].val = read();
    while (m--)
    {
        int opt = read(), x = read(), y = read();
        if (opt == 0)
            split(x, y), printf("%d\n", t[y].res);
        else if (opt == 1)
            link(x, y);
        else if (opt == 2)
            cut(x, y);
        else if (opt == 3)
            splay(x), t[x].val = y, pushUp(x);
    }
    return 0;
}
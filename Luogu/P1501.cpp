#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define int unsigned

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

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 5, mod = 51061;

struct node
{
    int ch[2], fa, tag, val, tagm, tagp, res, size;
} t[maxn];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define get(u) (rs(t[u].fa) == u)
#define isRoot(u) (ls(t[u].fa) != u && rs(t[u].fa) != u)

il void pushUp(int u)
{
    t[u].res = (t[ls(u)].res + t[rs(u)].res + t[u].val) % mod;
    t[u].size = t[ls(u)].size + t[rs(u)].size + 1;
    return;
}

il void pushR(int u)
{
    t[u].tag ^= 1;
    swap(ls(u), rs(u));
    return;
}

il void pushM(int u, int c)
{
    (t[u].tagm *= c) %= mod;
    (t[u].tagp *= c) %= mod;
    (t[u].val *= c) %= mod;
    (t[u].res *= c) %= mod;
    return;
}

il void pushP(int u, int c)
{
    (t[u].tagp += c) %= mod;
    (t[u].val += c) %= mod;
    (t[u].res += t[u].size * c % mod) %= mod;
    return;
}

il void pushDown(int u)
{
    if (t[u].tag)
    {
        if (ls(u)) pushR(ls(u));
        if (rs(u)) pushR(rs(u));
        t[u].tag ^= 1;
    }
    if (t[u].tagm != 1)
    {
        if (ls(u)) pushM(ls(u), t[u].tagm);
        if (rs(u)) pushM(rs(u), t[u].tagm);
        t[u].tagm = 1;
    }
    if (t[u].tagp)
    {
        if (ls(u)) pushP(ls(u), t[u].tagp);
        if (rs(u)) pushP(rs(u), t[u].tagp);
        t[u].tagp = 0;
    }
    return;
}

int stk[maxn], top;

il void pushAll(int u)
{
    stk[++top] = u;
    while (!isRoot(u)) stk[++top] = u = t[u].fa;
    while (top) pushDown(stk[top--]);
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

void splay(int u)
{
    pushAll(u);
    for (int fa; fa = t[u].fa, !isRoot(u); rotate(u))
        if (!isRoot(fa))
            rotate(get(u) == get(fa) ? fa : u);
    return;
}

int access(int u)
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

il void split(int u, int v)
{
    makeRoot(u), access(v);
    splay(v);
    return;
}

il void link(int u, int v)
{
    makeRoot(u), splay(u);
    t[u].fa = v;
    return;
}

il void cut(int u, int v)
{
    split(u, v);
    ls(v) = t[u].fa = 0;
    return;
}

signed main()
{
    int n = read(), q = read();
    FOR(i, 1, n) t[i].val = t[i].res = t[i].size = t[i].tagm = 1;
    FOR(i, 1, n - 1)
        link(read(), read());
    while (q--)
    {
        char c = getchar();
        int u = read(), v = read();
        if (c == '+')
        {
            split(u, v);
            pushP(v, read());
        }
        else if (c == '-')
        {
            cut(u, v);
            link(read(), read());
        }
        else if (c == '*')
        {
            split(u, v);
            pushM(v, read());
        }
        else if (c == '/')
        {
            split(u, v);
            printf("%u\n", t[v].res);
        }
    }
    return 0;
}
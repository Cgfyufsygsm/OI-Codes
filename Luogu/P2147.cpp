#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

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

template<typename T> inline void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e4 + 5;

struct node
{
    int ch[2], fa, size, tag;
} t[maxn];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

#define get(u) (rs(t[u].fa) == u)
#define isRoot(u) (ls(t[u].fa) != u && rs(t[u].fa) != u)

il void pushUp(int u)
{
    t[u].size = t[ls(u)].size + t[rs(u)].size + 1;
    return;
}

il void pushDown(int u)
{
    if (!t[u].tag) return;
    if (ls(u)) swap(ls(ls(u)), rs(ls(u))), t[ls(u)].tag ^= 1;
    if (rs(u)) swap(ls(rs(u)), rs(rs(u))), t[rs(u)].tag ^= 1;
    t[u].tag ^= 1;
    return;
}

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
        if (!isRoot(fa))
            rotate(get(u) == get(fa) ? fa : u);
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
    splay(u);
    t[u].fa = v;
    return;
}

il void cut(int u, int v)
{
    makeRoot(u);
    access(v), splay(u);
    t[v].fa = rs(u) = 0;
    pushUp(u);
    return;
}

int main()
{
    int n = read(), m = read();
    char s[10];
    while (m--)
    {
        int u, v;
        scanf("%s %d %d", s, &u, &v);
        if (s[0] == 'Q')
            printf("%s\n", findRoot(u) == findRoot(v) ? "Yes" : "No");
        else if (s[0] == 'C')
            link(u, v);
        else if (s[0] == 'D')
            cut(u, v);
    }
    return 0;
}
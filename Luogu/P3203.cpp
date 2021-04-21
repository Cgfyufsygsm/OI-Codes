#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

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

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

struct node
{
    int ch[2], fa, tag, size;
} t[maxn];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

#define isRoot(u) (ls(t[u].fa) != u && rs(t[u].fa) != u)
#define get(u) (rs(t[u].fa) == u)

il void pushUp(int u)
{
    t[u].size = t[ls(u)].size + t[rs(u)].size + 1;
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
    for (int fa; fa = t[u].fa, !isRoot(u); rotate(u))
        if (!isRoot(fa))
            rotate(get(u) == get(fa) ? fa : u);
    return;
}

il void access(int u)
{
    for (int p = 0; u; p = u, u = t[u].fa)
        splay(u), rs(u) = p, pushUp(u);
    return;
}

int n;

int main()
{
    n = read();
    FOR(i, 1, n)
    {
        int k = read();
        ls(i) = rs(i) = 0;
        t[i].size = 1;
        if (i + k <= n) t[i].fa = i + k;
    }
    int m = read();
    while (m--)
    {
        int op = read(), i = read() + 1;
        access(i), splay(i);
        if (op == 1)
            printf("%d\n", t[i].size);
        else
        {
            int k = read();
            ls(i) = t[ls(i)].fa = 0;
            if (i + k <= n)
                t[i].fa = i + k;
            pushUp(i);
        }
    }
    return 0;
}
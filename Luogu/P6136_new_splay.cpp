#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

const int maxn = 2e6 + 5, inf = 2147483647-10;

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

struct node
{
    int ch[2], fa, val, cnt, size;
} t[maxn];

int root, tot;

#define get(u) (rs(t[u].fa) == u)

il void pushup(int u)
{
    t[u].size = t[ls(u)].size + t[rs(u)].size + t[u].cnt;
    return;
}

il void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa, k1 = get(u), k2 = get(fa);
    if (gfa) t[gfa].ch[k2] = u;
    t[fa].ch[k1] = t[u].ch[k1 ^ 1], t[t[u].ch[k1 ^ 1]].fa = fa;
    t[u].fa = gfa, t[fa].fa = u, t[u].ch[k1 ^ 1] = fa;
    pushup(fa), pushup(u);
}

void splay(int u, int goal)
{
    for (int fa; fa = t[u].fa, fa != goal; rotate(u))
        if (t[fa].fa != goal)
            rotate(get(u) == get(fa) ? fa : u);
    if (!goal) root = u;
    return;
}

void insert(int val)
{
    int u = root, fa = 0;
    while (u && t[u].val != val)
        fa = u, u = t[u].ch[t[u].val < val];
    if (u) ++t[u].cnt;
    else
    {
        u = ++tot;
        if (fa) t[fa].ch[t[fa].val < val] = u;
        t[u].fa = fa, t[u].size = t[u].cnt = 1, t[u].val = val;
    }
    splay(u, 0);
    return;
}

int find(int val)
{
    int u = root;
    while (t[u].val != val && t[u].ch[t[u].val < val])
        u = t[u].ch[t[u].val < val];
    return u;
}

void delnode(int val)
{
    splay(find(val), 0);
    if (t[root].val != val) return;
    if (t[root].cnt > 1)
    {
        --t[root].cnt, --t[root].size;
        return;
    }
    if (!ls(root) || !rs(root))
        root = ls(root) + rs(root);
    else
    {
        int lmax = ls(root);
        while (rs(lmax)) lmax = rs(lmax);
        splay(lmax, root);
        t[rs(root)].fa = lmax;
        rs(lmax) = rs(root);
        pushup(root = lmax);
    }
    t[root].fa = 0;
    return;
}

int rank(int val)
{
    insert(val);
    int ret = t[ls(root)].size + 1;
    delnode(val);
    return ret;
}

int kth(int k)
{
    int u = root;
    while (true)
    {
        if (k <= t[ls(u)].size) u = ls(u);
        else if (k > t[ls(u)].size + t[u].cnt)
            k -= t[ls(u)].size + t[u].cnt, u = rs(u);
        else return t[u].val;
    }
}

int getnxt(int val, int op)
{
    insert(val);
    int u = t[root].ch[op], ret = t[u].val;
    while (t[u].ch[op ^ 1])
        u = t[u].ch[op ^ 1], ret = t[u].val;
    delnode(val);
    return ret;
}

int main()
{
    insert(inf), insert(-inf);
    int n = read(), m = read();
    while (n--) insert(read());
    int ans = 0, last = 0;
    while (m--)
    {
        int op = read(), x = read() ^ last;
        if (op == 1) insert(x);
        else if (op == 2) delnode(x);
        else if (op == 3) ans ^= (last = rank(x) - 1);
        else if (op == 4) ans ^= (last = kth(x + 1));
        else if (op == 5) ans ^= (last = getnxt(x, 0));
        else if (op == 6) ans ^= (last = getnxt(x, 1));
    }
    printf("%d\n", ans);
    return 0;
}
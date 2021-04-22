#include <cstdio>
#include <cctype>
#define L (t[u].ch[0])
#define R (t[u].ch[1])

const int maxn = 100000+5;

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline void swap(int &a, int &b)
{
    int t = a; a = b; b = t;
    return;
}

struct Splay
{
    int ch[2], fa;
    int size, val;
    int mark;
} t[maxn];

int root, cnt, n, m;

void maintain(int u)
{
    t[u].size = t[L].size + t[R].size + 1;
    return;
}

int get(int u)
{
    return t[t[u].fa].ch[1] == u;
}

inline void pushdown(int u)
{
    if (t[u].mark && u)
    {
        swap(L, R);
        t[L].mark ^= 1;
        t[R].mark ^= 1;
        t[u].mark = 0;
    }
    return;
}

void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa;
    pushdown(fa); pushdown(u);
    int d1 = get(u), d2 = get(fa);
    t[fa].ch[d1] = t[u].ch[d1 ^ 1];
    t[t[u].ch[d1 ^ 1]].fa = fa;
    t[u].ch[d1 ^ 1] = fa;
    t[fa].fa = u;
    if (gfa)
        t[gfa].ch[d2] = u;
    t[u].fa = gfa;
    maintain(fa);
    maintain(u);
    return;
}

void splay(int u, int goal)
{
    pushdown(u);
    while (t[u].fa != goal)
    {
        int fa = t[u].fa, gfa = t[fa].fa;
        int d1 = get(u), d2 = get(fa);
        if (gfa != goal)
        {
            if (d1 == d2)
                rotate(fa);
            else rotate(u);
        }
        rotate(u);
    }
    if (!goal)
        root = u;
    return;
}

void build(int i, int j, int &u, int fa)
{
    int cur = (i + j) >> 1;
    u = ++cnt;
    t[u].fa = fa;
    t[u].size = 1;
    if (cur == 1)
        t[u].val = -(maxn << 1);
    else if (cur == n + 2)
        t[u].val = maxn << 1;
    else
        t[u].val = cur - 1;
    if (cur > i)
        build(i, cur - 1, t[u].ch[0], u);
    if (cur < j)
        build(cur + 1, j, t[u].ch[1], u);
    maintain(u);
    return;
}

int find(int val)
{
    int u = root;
    while (1)
    {
        pushdown(u);
        if (val <= t[L].size)
            u = L;
        else
        {
            val -= t[L].size + 1;
            if (!val)
                return u;
            u = R;
        }
    }
}

void reverse(int l, int r)
{
    splay(find(l - 1), 0);
    splay(find(r + 1), root);
    int u = t[root].ch[1];
    u = t[u].ch[0];
    t[u].mark ^= 1;
    return;
}

void dfs(int u)
{
    if (!u)
        return;
    pushdown(u);
    dfs(L);
    if (t[u].val <= 0 || t[u].val > n + 1);
    else
        printf("%d ", t[u].val);
    dfs(R);
    return;
}

int main()
{
    n = read(), m = read();
    build(1, n + 2, root, 0);
    while (m--)
    {
        int l = read() + 1, r = read() + 1;
        reverse(l, r);
    }
    dfs(root);
    return 0;
}
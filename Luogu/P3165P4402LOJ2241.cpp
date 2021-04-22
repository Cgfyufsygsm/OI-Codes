#include <cstdio>
#include <cctype>
#include <algorithm>
#define L (t[u].ch[0])
#define R (t[u].ch[1])

using std::sort;

inline int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = s  *10 + c- '0' , c = getchar();
    return s;
}

const int maxn = 100000 + 5, inf = 1e9;

struct item
{
    int h, idx, treeid;
    bool operator<(const item &b) const
    {
        return h == b.h ? idx < b.idx : h < b.h;
    }
} init[maxn];

int id[maxn];

struct node
{
    item val;
    int size;
    int mark;
    int ch[2], fa;
} t[maxn];

int n, cnt, root;

inline void maintain(int u)
{
    t[u].size = t[L].size + t[R].size + 1;
    return;
}

inline void pushdown(int u)
{
    if (t[u].mark)
    {
        int tmp = L; L = R; R = tmp;
        t[L].mark ^= 1;
        t[R].mark ^= 1;
        t[u].mark = 0;
    }
    return;
}

inline int get(int u)
{
    pushdown(t[u].fa);
    return t[t[u].fa].ch[1] == u;
}

void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa;
    if (gfa)
        pushdown(gfa);
    pushdown(fa), pushdown(u);
    int d1 = get(u), d2 = get(fa);
    t[fa].ch[d1] = t[u].ch[d1 ^ 1], t[t[u].ch[d1 ^ 1]].fa = fa;
    if (gfa)
        t[gfa].ch[d2] = u;
    t[u].fa = gfa;
    t[fa].fa = u, t[u].ch[d1 ^ 1] = fa;
    maintain(fa);
    maintain(u);
}

void splay(int u, int goal)
{
    while (t[u].fa != goal)
    {
        int fa = t[u].fa, gfa = t[fa].fa;
        if (gfa)
            pushdown(gfa);
        pushdown(fa);
        pushdown(u);
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
    init[cur].treeid = u;
    t[u].val = init[cur];
    t[u].size = 1;
    t[u].fa = fa;
    if (cur > i)
        build(i, cur - 1, L, u);
    if (cur < j)
        build(cur + 1, j, R, u);
    maintain(u);
    return;
}

int findkth(int k)
{
    int u = root;
    while (true)
    {
        pushdown(u);
        int lsize = 0;
        if (L)
            lsize = t[L].size;
        if (k <= lsize)
            u = L;
        else if (k > lsize + 1)
            k -= lsize + 1, u = R;
        else return u;
    }
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        init[i].h = read();
        init[i].idx = i;
    }
    init[0].h = -inf, init[0].idx = 0;
    init[n + 1].h = inf, init[0].idx = n + 1;
    build(0, n + 1, root, 0);
    sort(init, init + n + 1);
    for (int i = 1; i <= n; i++)
    {
        splay(init[i].treeid, 0);
        int ans = t[t[root].ch[0]].size;
        printf("%d ", ans);
        splay(findkth(i), 0);
        splay(findkth(ans + 2), root);
        t[t[t[root].ch[1]].ch[0]].mark ^= 1;
    }
    return 0;
}
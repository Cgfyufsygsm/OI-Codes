#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#define il inline

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

typedef unsigned int ui;
ui randNum( ui& seed , ui last , const ui m)
{
    seed = seed * 17 + last ; return seed % m + 1; 
}

const int maxn = 1e6 + 5;

struct player
{
    int ac, time;
    il bool operator<(const player &b) const
    {
        return ac == b.ac ? time < b.time : ac > b.ac;
    }
    il bool operator==(const player &b) const
    {
        return ac == b.ac && time == b.time;
    }
    il bool operator<=(const player &b) const
    {
        return (*this) < b || (*this) == b;
    }
} p[maxn];

il player less(player val)
{
    player ret = val;
    --ret.time;
    return ret;
}

struct node
{
    player val;
    int key;
    int size;
    int ch[2];
    #define L (t[u].ch[0])
    #define R (t[u].ch[1])
} t[maxn];

int cnt, root;

il int newnode(player val)
{
    t[++cnt].val = val;
    t[cnt].key = rand();
    t[cnt].ch[0] = t[cnt].ch[1] = 0;
    t[cnt].size = 1;
    return cnt;
}

il void pushup(int u)
{
    t[u].size = t[L].size + t[R].size + 1;
    return;
}

void split(int u, player k, int &x, int &y)
{
    if (!u)
    {
        x = y = 0;
        return;
    }
    if (t[u].val <= k)
        x = u, split(R, k, R, y);
    else
        y = u, split(L, k, x, L);
    pushup(u);
    return;
}

int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (t[x].key < t[y].key)
        return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else
        return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void insert(player val)
{
    int u = newnode(val), x, y;
    split(root, val, x, y);
    root = merge(merge(x, u), y);
    return;
}

void delnode(player val)
{
    int x, y, z;
    split(root, less(val), x, y);
    split(y, val, y, z);
    y = merge(t[y].ch[0], t[y].ch[1]);
    root = merge(merge(x, y), z);
    return;
}

int rank(player val)
{
    int x, y;
    split(root, less(val), x, y);
    int ans = t[x].size;
    return root = merge(x, y), ans;
}

int main()
{
    int T = read();
    ui last = 7;
    while (T--)
    {
        ui m = read(), n = read(), seed = read(), ria, rib;
        memset(p, 0, sizeof p);
        cnt = root = 0;
        while (n--)
        {
            ria = randNum(seed, last, m);
            rib = randNum(seed, last, m);
            delnode(p[ria]);
            ++p[ria].ac, p[ria].time += rib;
            insert(p[ria]);
            printf("%d\n", last = rank(p[ria]));
        }
    }
    return 0;
}
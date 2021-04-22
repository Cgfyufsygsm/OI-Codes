#include <cstdio>
#include <cctype>
#include <cstdlib>

const int maxn = 1e5;

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

struct node
{
    int val, key;
    int size;
    int ch[2], fa;
    int tag;
    #define L (t[u].ch[0])
    #define R (t[u].ch[1])
} t[maxn];

int root, cnt, treepos[maxn];

inline int newnode(int val)
{
    t[++cnt].size = 1;
    t[cnt].val = val;
    t[cnt].key = rand();
    treepos[val] = cnt;
    return cnt;
}

inline void pushup(int u)
{
    t[u].size = 1;
    if (L)
        t[u].size += t[L].size, t[L].fa = u;
    if (R)
        t[u].size += t[R].size, t[R].fa = u;
    return;
}

void split(int u, int size, int &x, int &y)
{
    if (!u)
    {
        x = y = 0;
        return;
    }
    if (t[L].size < size)
        x = u, split(R, size - t[L].size - 1, R, y);
    else
        y = u, split(L, size, x, L);
    pushup(u);
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

int getrank(int u)
{
    int ret = t[L].size + 1;
    while (t[u].fa)
    {
        if (t[t[u].fa].ch[1] == u)
            ret += t[t[t[u].fa].ch[0]].size + 1;
        u = t[u].fa;
    }
    return ret;
}

int kth(int k)
{
    int u = root;
    while (true)
    {
        int lsize = 0;
        if (L)
            lsize = t[L].size;
        if (k <= lsize)
            u = L;
        else if (k > lsize + 1)
            k -= lsize + 1, u = R;
        else return t[u].val;
    }
}

int main()
{
    srand(20041031);
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        root = merge(root, newnode(read()));
    char opt[10];
    int s, t;
    while (m--)
    {
        scanf("%s", opt);
        s = read();
        if (opt[0] == 'T')
        {
            int rnk = getrank(treepos[s]);
            int x, y, z;
            split(root, rnk - 1, x, y);
            split(y, 1, y, z);
            root = merge(merge(y, x), z);
        }
        else if (opt[0] == 'B')
        {
            int rnk = getrank(treepos[s]);
            int x, y, z;
            split(root, rnk - 1, x, y);
            split(y, 1, y, z);
            root = merge(x, merge(z, y));
        }
        else if (opt[0] == 'I')
        {
            t = read();
            if (!t)
                continue;
            int x, y, z, w;
            int rnk = getrank(treepos[s]);
            split(root, rnk - 1 - (t < 0), x, y);
            split(y, 1, y, z);
            split(z, 1, z, w);
            root = merge(merge(x, z), merge(y, w));
        }
        else if (opt[0] == 'A')
            printf("%d\n", getrank(treepos[s]) - 1);
        else if (opt[0] == 'Q')
            printf("%d\n", kth(s));
    }
    return 0;
}
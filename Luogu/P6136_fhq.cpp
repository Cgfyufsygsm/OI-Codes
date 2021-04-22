#include <cstdio>
#include <cctype>
#include <cstdlib>

const int maxn = 1e6 + 2e5;

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
    int size;
    int ch[2];
    int val, key;
    #define L (t[u].ch[0])
    #define R (t[u].ch[1])
} t[maxn];

int cnt, root;

inline void pushup(int u)
{
    t[u].size = t[L].size + t[R].size + 1;
    return;
}

void split(int u, int k, int &x, int &y)
{
    if (!u)
    {
        x = y = 0;
        return;
    }
    if (t[u].val <= k)
    {
        x = u;
        split(R, k, R, y);
    }
    else
    {
        y = u;
        split(L, k, x, L);
    }
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

void insert(int val)
{
    t[++cnt].val = val;
    t[cnt].key = rand();
    t[cnt].size = 1;
    int x, y;
    split(root, val, x, y);
    root = merge(merge(x, cnt), y);
    return;
}

void delnode(int val)
{
    int x, y, z;
    split(root, val - 1, x, y);
    split(y, val, y, z);
    y = merge(t[y].ch[0], t[y].ch[1]);
    root = merge(merge(x, y), z);
    return;
}

int rank(int val)
{
    int x, y;
    split(root, val - 1, x, y);
    int ans = t[x].size + 1;
    return root = merge(x, y), ans;
}

int kth(int k)
{
    int u = root;
    while (true)
    {
        int lsize = 0;
        if (L) lsize = t[L].size;
        if (k <= lsize)
            u = L;
        else if (k > lsize + 1)
            k -= lsize + 1, u = R;
        else return t[u].val;
    }
}

int pre(int val)
{
    return kth(rank(val) - 1);
}

int suc(int val)
{
    return kth(rank(val + 1));
}

int main()
{
    int n = read(), m = read(), ans = 0, lastans = 0;
    srand(20041031);
    while (n--)
        insert(read());
    while (m--)
    {
        int opt = read(), x = read() ^ lastans;
        switch (opt)
        {
        case 1:
            insert(x);
            break;
        case 2:
            delnode(x);
            break;
        case 3:
            ans ^= (lastans = rank(x));
            break;
        case 4:
            ans ^= (lastans = kth(x));
            break;
        case 5:
            ans ^= (lastans = pre(x));
            break;
        case 6:
            ans ^= (lastans = suc(x));
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
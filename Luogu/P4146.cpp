#include <cstdio>
#include <cctype>
#include <cstdlib>

const int maxn = 100000 + 5;

template<typename T> inline T max(T a, T b){return a > b ? a : b;}

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
    int ch[2], size;
    int val, maxval, key;
    int rev, add;
    #define L t[u].ch[0]
    #define R t[u].ch[1]
} t[maxn];

int cnt, root;

inline void pushdown(int u)
{
    if (t[u].rev)
    {
        int tmp = L; L = R; R = tmp;
        if (L) t[L].rev ^= 1;
        if (R) t[R].rev ^= 1;
        t[u].rev = 0;
    }
    if (t[u].add)
    {
        for (int i = 1, k = L; i <= 2; k = R, ++i)
        {
            t[k].add += t[u].add;
            t[k].val += t[u].add;
            t[k].maxval += t[u].add;
        }
        t[u].add = 0;
    }
    return;
}

inline void pushup(int u)
{
    pushdown(u);
    t[u].size = t[L].size + t[R].size + 1;
    t[u].maxval = t[u].val;
    if (L)
        t[u].maxval = max(t[u].maxval, t[L].maxval);
    if (R)
        t[u].maxval = max(t[u].maxval, t[R].maxval);
    return;
}

inline int newnode(int val)
{
    t[++cnt].size = 1;
    t[cnt].val = t[cnt].maxval = val;
    t[cnt].key = rand();
    return cnt;
}

void split(int u, int size, int &x, int &y)
{
    if (!u)
    {
        x = y = 0;
        return;
    }
    pushdown(u);
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
        return pushdown(x), t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else
        return pushdown(y), t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void add(int l, int r, int val)
{
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    t[y].val += val, t[y].add += val, t[y].maxval += val;
    root = merge(merge(x, y), z);
    return;
}

void reverse(int l, int r)
{
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    t[y].rev ^= 1;
    root = merge(merge(x, y), z);
    return;
}

int query(int l, int r)
{
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    int ans = t[y].maxval;
    return merge(merge(x, y), z), ans;
}

int main()
{
    int n = read(), m = read();
    while (n--)
        root = merge(root, newnode(0));
    while (m--)
    {
        int opt = read(), l = read(), r = read(), k = (opt == 1 ? read() : 0);
        if (opt == 1)
            add(l, r, k);
        else if (opt == 2)
            reverse(l, r);
        else printf("%d\n", query(l, r));
    }
    return 0;
}
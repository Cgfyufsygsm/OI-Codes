#include <cstdio>
#include <cctype>
#include <cstdlib>

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

struct node
{
    int ch[2];
    int size;
    int val, key;
    bool tag;
    #define L (t[u].ch[0])
    #define R (t[u].ch[1])
} t[maxn];

int cnt, root;

inline void pushup(int u)
{
    t[u].size = t[L].size + t[R].size + 1;
    return;
}

inline void pushdown(int u)
{
    if (t[u].tag)
    {
        int tmp = L; L = R; R = tmp;
        t[L].tag ^= 1, t[R].tag ^= 1;
        t[u].tag = 0;
    }
    return;
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
    return;
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

int newnode(int val)
{
    t[++cnt].val = val;
    t[cnt].key = rand();
    t[cnt].size = 1;
    return cnt;
}

void reverse(int l, int r)
{
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    t[y].tag ^= 1;
    root = merge(merge(x, y), z);
    return;
}

void dfs(int u)
{
    if (!u)
        return;
    pushdown(u);
    dfs(L);
    printf("%d ", t[u].val);
    dfs(R);
    return;
}

int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        root = merge(root, newnode(i));
    while (m--)
    {
        int l = read(), r = read();
        reverse(l, r);
    }
    dfs(root);
    return 0;
}
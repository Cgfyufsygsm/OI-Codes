#include <cstdio>
#include <cctype>
#include <cstdlib>

const int maxn = 1e5 + 5;

int n, m, q;

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

inline char readalpha()
{
    char c = getchar();
    while (!isalpha(c))
        c = getchar();
    return c;
}

inline void swap(int &x, int &y) {int tmp = x; x = y; y = tmp;}

struct treap
{
    int root, ch[2];
    int val, key;
    int size;
    #define L (t[u].ch[0])
    #define R (t[u].ch[1])
} t[maxn];

int find(int u)
{
    return t[u].root == u ? u : t[u].root = find(t[u].root);
}

void pushup(int u)
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
        x = u, split(R, k, R, y);
    else
        y = u, split(L, k, x, L);
    pushup(u);
}

int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (t[x].key <= t[y].key)
        return t[x].ch[1] = merge(t[x].ch[1], y), pushup(x), x;
    else
        return t[y].ch[0] = merge(x, t[y].ch[0]), pushup(y), y;
}

void insert(int &root, int u)
{
    int x, y;
    int val = t[u].val;
    split(root, val, x, y);
    root = merge(merge(x, u), y);
    return;
}

void dfs(int u, int &root)
{
    if (!u)
        return;
    dfs(L, root);
    dfs(R, root);
    L = R = 0;
    insert(root, u);
    return;
}

int join(int x, int y)
{
    if (t[x].size > t[y].size)
        swap(x, y);
    dfs(x, y);
    return y;
}

int kth(int u, int k)
{
    while (true)
    {
        if (k <= t[L].size)
            u = L;
        else if (k > t[L].size + 1)
            k -= t[L].size + 1, u = R;
        else return u;
    }
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
    {
        t[i].root = i;
        t[i].key = rand(), t[i].val = read();
        t[i].size = 1;
    }
    for (int i = 1, x, y, rt; i <= m; ++i)
    {
        x = read(), y = read();
        if (find(x) == find(y))
            continue;
        rt = join(t[x].root, t[y].root);
        t[find(x)].root = t[find(y)].root = rt;
        t[rt].root = rt;
    }
    q = read();
    while (q--)
    {
        char op = readalpha();
        int x = read(), y = read();
        if (op == 'B')
        {
            if (find(x) == find(y))
                continue;
            int rt = join(t[x].root, t[y].root);
            t[find(x)].root = t[find(y)].root = rt;
            t[rt].root = rt;
        }
        else
            printf("%d\n", t[find(x)].size < y ? -1 : kth(find(x), y));
    }
    return 0;
}
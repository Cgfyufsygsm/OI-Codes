#include <cstdio>
#include <cctype>
#define L t[u].ch[0]
#define R t[u].ch[1]

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

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

const int maxn = 1e5 + 5, inf = 2147483647-20;
int cnt, root;

struct Splay
{
    int ch[2], fa;
    int cnt, size;
    int val;
} t[maxn];

inline bool get(int u)
{
    return t[t[u].fa].ch[1] == u;
}

inline void maintain(int u)
{
    t[u].size = t[u].cnt + t[L].size + t[R].size;
    return;
}

void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa;
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
        int d1 = get(u), d2 = get(fa);
        if (gfa != goal)
        {
            if (d1 == d2)
                rotate(fa);
            else
                rotate(u);
        }
        rotate(u);
    }
    if (goal == 0)
        root = u;
}

void insert(int val)
{
    int u = root, fa = 0;
    while (u && t[u].val != val)
        fa = u, u = t[u].ch[t[u].val < val];
    if (u)
        t[u].cnt++;
    else
    {
        u = ++cnt;
        if (fa)
            t[fa].ch[t[fa].val < val] = u;
        t[u].fa = fa;
        t[u].size = t[u].cnt = 1;
        t[u].val = val;
    }
    splay(u, 0);
}

int find(int val)
{
    int u = root;
    while (t[u].val != val && t[u].ch[t[u].val < val])
        u = t[u].ch[t[u].val < val];
    return u;
}

int kth(int k)
{
    int u = root;
    while (true)
    {
        if (k <= t[L].size)
            u = L;
        else if (k > t[L].size + t[u].cnt)
        {
            k -= t[L].size + t[u].cnt;
            u = R;
        }
        else
            return t[u].val;
    }
}

void delnode(int val)
{
    splay(find(val), 0);
    if (t[root].val != val)
        return;
    if (t[root].cnt > 1)
    {
        t[root].cnt--;
        t[root].size--;
        return;
    }
    if ((!t[root].ch[0]) || (!t[root].ch[1]))
        root = t[root].ch[0] + t[root].ch[1];
    else
    {
        int lmax = t[root].ch[0];
        while (t[lmax].ch[1])
            lmax = t[lmax].ch[1];
        splay(lmax, root);
        t[t[root].ch[1]].fa = lmax;
        t[lmax].ch[1] = t[root].ch[1];
        maintain(root = lmax);
    }
    t[root].fa = 0;
    return;
}

int rank(int val)
{
    insert(val);
    int ans = t[t[root].ch[0]].size + 1;
    delnode(val);
    return ans;
}

int getnxt(int val,int opt)
{
    insert(val);
    int u = t[root].ch[opt], ans = t[u].val;
    while (t[u].ch[opt ^ 1])
        u = t[u].ch[opt ^ 1], ans = t[u].val;
    delnode(val);
    return ans;
}

int main()
{
    insert(inf), insert(-inf);
    int n = read();
    while (n--)
    {
        int opt = read(), x = read();
        switch (opt)
        {
        case 1:
            insert(x);
            break;
        case 2:
            delnode(x);
            break;
        case 3:
            printf("%d\n", rank(x) - 1);
            break;
        case 4:
            printf("%d\n", kth(x+1));
            break;
        case 5:
            printf("%d\n", getnxt(x, 0));
            break;
        case 6:
            printf("%d\n", getnxt(x, 1));
            break;
        }
    }
    return 0;
}
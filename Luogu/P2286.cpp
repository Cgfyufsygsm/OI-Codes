#include <cstdio>
#include <cctype>
#define L (t[u].ch[0])
#define R (t[u].ch[1])

typedef long long ll;

const ll maxn = 80005, mod = 1000000, inf = (1ll<<31) + 1;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline ll abs(ll x){return x < 0 ? -x : x;}

struct node
{
    ll size, val, cnt;
    int ch[2], fa;
} t[maxn];

int cnt, root, ans;

inline void maintain(int u)
{
    t[u].size = t[L].size + t[R].size + t[u].cnt;
    return;
}

inline int get(int u)
{
    return t[t[u].fa].ch[1] == u;
}

void rotate(int u)
{
    int fa = t[u].fa, gfa = t[fa].fa;
    int d1 = get(u), d2 = get(fa);
    t[fa].ch[d1] = t[u].ch[d1 ^ 1];
    t[t[u].ch[d1 ^ 1]].fa = fa;
    if (gfa)
        t[gfa].ch[d2] = u;
    t[u].fa = gfa;
    t[fa].fa = u;
    t[u].ch[d1 ^ 1] = fa;
    maintain(fa);
    maintain(u);
    return;
}

void splay(int u, int goal)
{
    while (t[u].fa != goal)
    {
        int fa = t[u].fa, gfa = t[fa].fa;
        int d1 = get(u), d2 = get(fa);
        if (gfa != goal)
        {
            if (d1 != d2)
                rotate(u);
            else rotate(fa);
        }
        rotate(u);
    }
    if(goal == 0)
        root = u;
    return;
}

void insert(ll val)
{
    int u = root, fa = 0;
    while (u && t[u].val != val)
        fa = u, u = t[u].ch[val > t[u].val];
    if (u)
        t[u].cnt++, t[u].size++;
    else
    {
        u = ++cnt;
        t[u].val = val;
        t[u].cnt = t[u].size = 1ll;
        if (fa)
            t[fa].ch[val > t[fa].val] = u;
        t[u].fa = fa;
    }
    splay(u, 0);
    return;
}

int find(ll val)
{
    int u = root;
    while (t[u].val != val && t[u].ch[val > t[u].val])
        u = t[u].ch[val > t[u].val];
    return u;
}

void delnode(ll val)
{
    splay(find(val), 0);
    if (t[root].cnt > 1)
    {
        t[root].cnt--;
        t[root].size--;
        return;
    }
    if (!(t[root].ch[0]) || !(t[root].ch[1]))
    {
        root = t[root].ch[0] + t[root].ch[1];
        t[root].fa = 0;
        return;
    }
    int lmax = t[root].ch[0];
    while (t[lmax].ch[1])
        lmax = t[lmax].ch[1];
    splay(lmax, root);
    t[lmax].ch[1] = t[root].ch[1];
    t[t[root].ch[1]].fa = lmax;
    maintain(root = lmax);
    t[root].fa = 0;
    return;
}

int getnxt(ll val, int opt)
{
    splay(find(val), 0);
    if (t[root].val <= val && (!opt))
        return t[root].val;
    if (t[root].val >= val && opt)
        return t[root].val;
    int u = t[root].ch[opt];
    while (t[u].ch[opt ^ 1])
        u = t[u].ch[opt ^ 1];
    return t[u].val;
}

int main()
{
    int n = read();
    int tmp = 0;//宠物数量
    insert(-inf), insert(inf);
    while (n--)
    {
        int a = read() ? -1 : 1, b = read();
        if ((!tmp) || (tmp > 0 && a > 0) || (tmp < 0 && a < 0))
            insert(b);
        else if (t[root].size == 1)
        {
            ans = (ans + abs(t[root].val - b)) % mod;
            delnode(t[root].val);
        }
        else
        {
            int pre = getnxt(b, 0), suc = getnxt(b, 1);
            int d1 = abs(pre - b), d2 = abs(suc - b);
            if (d1 <= d2)
            {
                ans = (ans + d1) % mod;
                delnode(pre);
            }
            else
            {
                ans = (ans + d2) % mod;
                delnode(suc);
            }
        }
        tmp += a;
    }
    printf("%d\n", ans);
    return 0;
}
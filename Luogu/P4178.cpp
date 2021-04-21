#include <cstdio>
#include <cctype>
#define lowbit(x) (x & -x)
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

const int maxn = 4e4 + 5;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a, int b) {return a > b ? a : b;}

int n, k;
int head[maxn], cnte;

struct edge
{
    int to, nxt, w;
} e[maxn << 1];


inline void add(int u, int v, int w)
{
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

int root, tot, size[maxn], maxp[maxn], vis[maxn];

void getrt(int u, int fa)
{
    size[u] = 1, maxp[u] = 0;
    GO(u)
    {
        if (v == fa || vis[v]) continue;
        getrt(v, u);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

const int maxdis = 4e7 + 5;
int bit[maxdis], ans;
int dis[maxn], rem[maxdis], q[maxn];

void ins(int x, int v)
{
    int x0 = x;
    for (; x < maxdis; x += lowbit(x))
        bit[x] += v;
    return;
}

int query(int x)
{
    if (x <= 0) return 0;
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += bit[x];
    return ret;
}

void getdis(int u, int fa)
{
    rem[++rem[0]] = dis[u];
    GO(u)
    {
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
    return;
}

void calc(int u)
{
    int p = 0;
    int tmp = 0;
    GO(u)
    {
        if (vis[v]) continue;
        rem[0] = 0;
        dis[v] = e[i].w;
        getdis(v, u);
        DEC(j, rem[0], 1)
        {
            ans += query(k - rem[j]);
            tmp += query(k - rem[j]);
            if (k >= rem[j]) ++ans, ++tmp;
        }
        DEC(j, rem[0], 1)
            q[++p] = rem[j], ins(rem[j], 1);
    }
    FOR(i, 1, p)
        ins(q[i], -1);
    return;
}

void divide(int u)
{
    vis[u] = 1;
    calc(u);
    GO(u)
    {
        if (vis[v]) continue;
        maxp[0] = n, tot = size[v], root = 0;
        getrt(v, u);
        getrt(root, 0);
        divide(root);
    }
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    k = read();
    maxp[root = 0] = n;
    getrt(1, 0);
    getrt(root, 0);
    divide(root);
    printf("%d\n", ans);
    return 0;
}
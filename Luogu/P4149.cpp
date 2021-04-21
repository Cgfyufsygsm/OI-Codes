#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

const int maxn = 2e5 + 5;

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
inline int min(int a, int b) {return a < b ? a : b;}

int n, k, ans = 1e9;
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

int size[maxn], maxp[maxn], root, vis[maxn], tot;

void getrt(int u, int fa)
{
    size[u] = 1, maxp[u] = 0;
    GO(u)
    {
        if (vis[v] || v == fa) continue;
        getrt(v, u);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], tot - maxp[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

const int maxk = 1e6 + 5;
int dis[maxn], dep[maxn];
int mind[maxk];

struct node
{
    int dis, dep;
} tmp[maxn];

int tmpcnt, q[maxn];

void getdis(int u, int fa)
{
    if (dis[u] > k) return;
    tmp[++tmpcnt] = (node){dis[u], dep[u]};
    GO(u)
    {
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        dep[v] = dep[u] + 1;
        getdis(v, u);
    }
    return;
}

void calc(int u)
{
    dep[u] = 0;
    mind[0] = 0;
    int p = 0;
    GO(u)
    {
        if (vis[v]) continue;
        tmpcnt = 0;
        dis[v] = e[i].w;
        dep[v] = 1;
        getdis(v, u);
        FOR(j, 1, tmpcnt)
            ans = min(ans, tmp[j].dep + mind[k - tmp[j].dis]);
        FOR(j, 1, tmpcnt)
            mind[tmp[j].dis] = min(mind[tmp[j].dis], tmp[j].dep), q[++p] = tmp[j].dis;
    }
    FOR(i, 1, p) mind[q[i]] = 1e9;
    return;
}

void divide(int u)
{
    vis[u] = 1;
    calc(u);
    GO(u)
    {
        if (vis[v]) continue;
        tot = size[v], maxp[root = 0] = n;
        getrt(v, u);
        divide(root);
    }
    return;
}

int main()
{
    n = read(), k = read();
    memset(mind, 0x3f, sizeof mind);
    FOR(i, 1, n - 1)
    {
        int u = read() + 1, v = read() + 1, w = read();
        add(u, v, w), add(v, u, w);
    }
    tot = n, root = 0, maxp[0] = n;
    getrt(1, 0);
    divide(root);
    printf("%d\n", ans > n ? -1 : ans);
    return 0;
}
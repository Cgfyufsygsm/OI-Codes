#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e4 + 5, maxm = 105, maxk = 1e7 + 5;

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

int n, m, query[maxm], ans[maxk];
int head[maxn], cnte;

struct edge
{
    int to, nxt, w;
} e[maxn << 1];

inline void add(int u, int v, int w)
{
    e[++cnte].to = v;
    e[cnte].nxt = head[u];
    e[cnte].w = w;
    head[u] = cnte;
    return;
}

int size[maxn];
int maxp[maxn], vis[maxn], root, tot, rem[maxn];
int tmp[maxk], judge[maxk], q[maxn], dis[maxn];

void getrt(int u, int fa)
{
    size[u] = 1;
    maxp[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa || vis[v]) continue;
        getrt(v, u);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

void getdis(int u, int fa)
{
    rem[++rem[0]] = dis[u];
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
    return;
}

void calc(int u)
{
    int p = 0;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (vis[v]) continue;
        rem[0] = 0;
        dis[v] = e[i].w;
        getdis(v, u);
        DEC(j, rem[0], 1)
            FOR(k, 1, m)
                if (query[k] >= rem[j])
                    ans[k] |= judge[query[k] - rem[j]];
        DEC(j, rem[0], 1)
            q[++p] = rem[j], judge[rem[j]] = 1;
    }
    FOR(i, 1, p)
        judge[q[i]] = 0;
    return;
}

void solve(int u)
{
    vis[u] = judge[0] = 1;
    calc(u);
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (vis[v]) continue;
        maxp[0] = n, tot = size[v], root = 0;
        getrt(v, u);
        getrt(root, 0);
        solve(root);
    }
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    FOR(i, 1, m) query[i] = read();
    maxp[root = 0] = tot = n;
    getrt(1, 0);
    getrt(root, 0);
    solve(root);
    FOR(i, 1, m)
        puts(ans[i] ? "AYE" : "NAY");
    return 0;
}
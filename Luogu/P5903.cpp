#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 5e5 + 5;

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

#define ui unsigned int
ui s;

inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}
#undef ui

int n, q;

int head[maxn], to[maxn], nxt[maxn], cnt;
int dep[maxn], hson[maxn], h[maxn], top[maxn], fa[maxn][20], root, lg[maxn];
std::vector<int> down[maxn], up[maxn];

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs1(int u)
{
    dep[u] = dep[fa[u][0]] + 1;
    FOR(i, 1, 19)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    h[u] = -1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        dfs1(v);
        if (h[v] > h[u])
            h[u] = h[v], hson[u] = v;
    }
    ++h[u];
    if (!h[u])
        h[u] = 1;
}

void dfs2(int u, int topf)
{
    down[topf].push_back(u);
    if (u == topf)
    {
        int now = u;
        FOR(i, 1, h[u])
            up[u].push_back(now), now = fa[now][0];
    }
    top[u] = topf;
    if (hson[u])
        dfs2(hson[u], topf);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != hson[u])
            dfs2(v, v);
    }
    return;
}

int ask(int u, int k)
{
    if (!k) return u;
    int tod = dep[u] - k;
    u = top[fa[u][lg[k]]];
    int nowd = dep[u];
    if (nowd > tod)
        return up[u][nowd - tod];
    else return down[u][tod - nowd];
}

int main()
{
    n = read(), q = read(), s = read();
    lg[0] = -1;
    FOR(i, 1, n) lg[i] = lg[i >> 1] + 1;
    FOR(u, 1, n)
    {
        fa[u][0] = read();
        if (!fa[u][0]) root = u;
        else
            add(fa[u][0], u);
    }
    dfs1(root);
    dfs2(root, root);
    long long ans = 0, lastans = 0;
    FOR(i, 1, q)
    {
        int x = (get(s) ^ lastans) % n + 1, k = (get(s) ^ lastans) % dep[x];
        lastans = ask(x, k);
        ans ^= 1ll * lastans * i;
    }
    printf("%lld\n", ans);
    return 0;
}
#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 3e5 + 5;

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

typedef long long ll;

inline ll min(ll a, ll b) {return a < b ? a : b;}

int n, q;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
int size[maxn], h[maxn], son[maxn];
ll *f[maxn], buf[maxn << 1], *now = buf, ans[maxn];

struct node
{
    int id, k;
};

std::vector<node> query[maxn];

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (h[v] > h[son[u]])
            son[u] = v;
    }
    h[u] = h[son[u]] + 1;
    return;
}

void dfs2(int u, int fa, int dep)
{
    if (son[u])
        f[son[u]] = f[u] + 1, dfs2(son[u], u, dep + 1);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa || v == son[u]) continue;
        f[v] = now, now += h[v];
        dfs2(v, u, dep + 1);
        FOR(j, 1, h[v])
            f[u][j] += f[v][j - 1];
    }
    FOR(i, 0, (int)query[u].size() - 1)
    {
        int k = query[u][i].k, id = query[u][i].id;
        ans[id] += min(k, dep - 1) * 1ll * (size[u] - 1);
        if (k >= h[u] - 1)
            ans[id] += f[u][1];
        else ans[id] += f[u][1] - f[u][k + 1];
    }
    f[u][0] = f[u][1] + size[u] - 1;
}

int main()
{
    n = read(), q = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    FOR(i, 1, q)
        query[read()].push_back((node){i, read()});
    dfs1(1, 0);
    f[1] = now, now += h[1];
    dfs2(1, 0, 1);
    FOR(i, 1, q)
        printf("%lld\n", ans[i]);
    return 0;
}
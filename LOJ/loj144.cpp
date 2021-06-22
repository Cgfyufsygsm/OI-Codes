#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define lowbit(x) (x & -x)

const int maxn = 1e6 + 5;

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

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int n, dfn[maxn], low[maxn], cntdfn, m, root;

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int fa)
{
    dfn[u] = ++cntdfn;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa)
            dfs(v, u);
    }
    low[u] = cntdfn;
    return;
}

ll f[maxn], v[maxn];

void modify(int x, ll v)
{
    for (; x <= cntdfn; x += lowbit(x))
        f[x] += v;
    return;
}

ll sum(int x)
{
    ll ret = 0;
    for (; x; x -= lowbit(x))
        ret += f[x];
    return ret;
}

int main()
{
    n = read(), m = read(), root = read();
    FOR(i, 1, n) v[i] = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs(root, 0);
    FOR(i, 1, n) modify(dfn[i], v[i]);
    while (m--)
    {
        int op = read(), a = read();
        if (op == 1) modify(dfn[a], read());
        else printf("%lld\n", sum(low[a]) - sum(dfn[a] - 1));
    }
    return 0;
}
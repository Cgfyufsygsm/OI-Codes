#include <cstdio>
#include <cctype>
#define il inline
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
int n, dfn[maxn], nfd[maxn], low[maxn], cntdfn, m, root;

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int fa)
{
    dfn[u] = ++cntdfn, nfd[dfn[u]] = u;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa)
            dfs(v, u);
    }
    low[u] = cntdfn;
    return;
}

ll v[maxn], f[maxn << 2], tag[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushdown(int i, int j, int k)
{
    if (!tag[k]) return;
    f[L] += tag[k] * (M - i + 1);
    f[R] += tag[k] * (j - M);
    tag[L] += tag[k];
    tag[R] += tag[k];
    tag[k] = 0;
    return;
}

il void pushup(int k) {f[k] = f[L] + f[R]; return;}

void build(int i, int j, int k)
{
    if (i == j)
    {
        f[k] = v[nfd[i]];
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    pushup(k);
    return;
}

void modify(int i, int j, int k, int x, int y, ll d)
{
    if (x <= i && y >= j)
    {
        f[k] += d * (j - i + 1);
        tag[k] += d;
        return;
    }
    pushdown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, d);
    if (y > M) modify(M + 1, j, R, x, y, d);
    pushup(k);
    return;
}

ll query(int i, int j, int k, int x, int y)
{
    if (x <= i && y >= j) return f[k];
    pushdown(i, j, k);
    ll ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
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
    build(1, n, 1);
    while (m--)
    {
        int op = read(), u = read();
        if (op == 1) modify(1, n, 1, dfn[u], low[u], read());
        else printf("%lld\n", query(1, n, 1, dfn[u], low[u]));
    }
    return 0;
}
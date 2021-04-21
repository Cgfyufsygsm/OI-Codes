#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const int maxn = 1e5 + 5;

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

int n, c[maxn];

int head[maxn], to[maxn << 1], nxt[maxn << 1], tot;
int size[maxn], fa[maxn], son[maxn];

inline void add(int u, int v)
{
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
    return;
}

void dfs1(int u, int fat)
{
    size[u] = 1, fa[u] = fat;
    int maxson = -1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fat) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > maxson)
            maxson = size[v], son[u] = v;
    }
    return;
}

int flag, maxc, cnt[maxn];
ll sum, ans[maxn];

void calc(int u, int val)
{
    cnt[c[u]] += val;
    if (val > 0 && cnt[c[u]] > maxc)
        maxc = cnt[c[u]], sum = c[u];
    else if (val > 0 && cnt[c[u]] == maxc)
        sum += c[u];
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != fa[u] && to[i] != flag)
            calc(to[i], val);
    return;
}

void dfs2(int u, int keep)
{
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != fa[u] && to[i] != son[u])
            dfs2(to[i], 0);
    if (son[u]) dfs2(son[u], 1), flag = son[u];
    calc(u, 1);
    ans[u] = sum;
    flag = 0;
    if (!keep) calc(u, -1), sum = maxc = 0;
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n) c[i] = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    FOR(i, 1, n) printf("%lld ", ans[i]);
    return 0;
}
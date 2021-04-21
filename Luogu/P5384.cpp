#include <cstdio>
#include <cctype>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

struct node
{
    int id, k;
};

int n, q;
std::vector<node> query[maxn], rq[maxn];
int head[maxn], to[maxn], nxt[maxn], cnt;
int h[maxn], son[maxn];
int ans[maxn];
int *f[maxn], buf[maxn << 3], *now = buf;

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int stk[maxn], top;

void dfs1(int u)
{
    stk[++top] = u;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        dfs1(v);
        if (h[v] > h[son[u]])
            son[u] = v;
    }
    h[u] = h[son[u]] + 1;
    FOR(i, 0, (int)query[u].size() - 1)
        if (top > query[u][i].k)
            rq[stk[top - query[u][i].k]].push_back(query[u][i]);
    --top;
    return;
}

void dfs2(int u)
{
    f[u][0] = 1;
    if (son[u])
        f[son[u]] = f[u] + 1, dfs2(son[u]);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == son[u]) continue;
        f[v] = now, now += h[v];
        dfs2(v);
        FOR(i, 1, h[v])
            f[u][i] += f[v][i - 1];
    }
    FOR(i, 0, (int)rq[u].size() - 1)
        ans[rq[u][i].id] = f[u][rq[u][i].k] - 1;
    return;
}

int main()
{
    n = read(), q = read();
    FOR(i, 2, n) add(read(), i);
    FOR(i, 1, q)
    {
        int u = read(), k = read();
        query[u].push_back((node){i, k});
    }
    dfs1(1);
    f[1] = now, now += h[1];
    dfs2(1);
    FOR(i, 1, q) printf("%d ", ans[i]);
    return 0;
}
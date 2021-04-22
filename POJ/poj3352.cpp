#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1005;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt = 1;
int n, r;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b) {return a < b ? a : b;}

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

int dfn[maxn], low[maxn], bel[maxn], bccCnt, dfnClock;
int bridge[maxn << 1];
int deg[maxn];

void tarjan(int u, int last)
{
    dfn[u] = low[u] = ++dfnClock;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (!dfn[v])
        {
            tarjan(v, i);
            if (low[v] > dfn[u])
                bridge[i] = bridge[i ^ 1] = 1;
            low[u] = min(low[u], low[v]);
        }
        else if (i != (last ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
    return;
}

void dfs(int u, int nowbcc)
{
    bel[u] = nowbcc;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (bel[v] || bridge[i]) continue;
        dfs(v, nowbcc);
    }
    return;
}

int main()
{
    n = read(), r = read();
    FOR(i, 1, r)
    {
        int u = read(), v = read();
        add(u, v);
        add(v, u);
    }
    FOR(i, 1, n)
        if (!dfn[i])
            tarjan(i, 0);
    FOR(i, 1, n)
        if (!bel[i])
            dfs(i, ++bccCnt);
    int ans = 0;
    FOR(u, 1, n)
        for (int i = head[u]; i; i = nxt[i])
        {
            int v = to[i];
            if (bel[u] != bel[v])
                ++deg[bel[u]], ++deg[bel[v]];
        }
    FOR(i, 1, bccCnt)
        if (deg[i] == 2)
            ++ans;
    
    if (ans & 1) ++ans;
    printf("%d\n", ans >>= 1);
    return 0;
}
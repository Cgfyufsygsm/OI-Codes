#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 3e5 + 5;

namespace before
{
    int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt = 1;
    int bel[maxn], dfn[maxn], low[maxn], idx;
    int stk[maxn], top = 0, newtot;

    void add(int u, int v)
    {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
        return;
    }

    void tarjan(int u, int from)
    {
        dfn[u] = low[u] = ++idx;
        stk[++top] = u;
        for (int i = head[u]; i; i = nxt[i])
        {
            int &v = to[i];
            if (i == (from ^ 1)) continue;
            if (!dfn[v])
            {
                tarjan(v, i);
                low[u] = min(low[u], low[v]);
            }
            else low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u])
        {
            ++newtot;
            int _u;
            do
            {
                _u = stk[top--];
                bel[_u] = newtot;
            } while (u != _u);
        }
        return;
    }
}

namespace after
{
    int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;

    void add(int u, int v)
    {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
        return;
    }

    int d, maxdist;
    
    void dfs(int u, int fa, int dist)
    {
        if (dist > maxdist)
            d = u, maxdist = dist;
        for (int i = head[u]; i; i = nxt[i])
        {
            int &v = to[i];
            if (v == fa)
                continue;
            dfs(v, u, dist + 1);
        }
        return;
    }
}

namespace before
{
    bool vis[maxn];
    void dfs(int u, int fa)
    {
        vis[u] = 1;
        for (int i = head[u]; i; i = nxt[i])
        {
            int &v = to[i];
            if (vis[v]) continue;
            if (bel[u] != bel[v])
            {
                after::add(bel[u], bel[v]);
                after::add(bel[v], bel[u]);
            }
            dfs(v, u);
        }
        return;
    }
}

int main()
{
    int n = read(), m = read();
    FOR(i, 1, m)
    {
        int u = read(), v = read();
        before::add(u, v);
        before::add(v, u);
    }
    before::tarjan(1, -1);
    before::dfs(1, 0);
    after::dfs(1, 0, 0);
    after::maxdist = 0;
    after::dfs(after::d, 0, 0);
    printf("%d\n", after::maxdist);
    return 0;
}
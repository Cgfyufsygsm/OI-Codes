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

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 200000 * 2 + 5;

namespace old
{
    int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
    int n, val[maxn];
    void add(int u, int v)
    {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }
}

namespace after
{
    int tot;
    int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
    void add(int u, int v)
    {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }
    int maxdist = 0, d = 0;
    void dfs(int u, int fa, int dist)
    {
        if (dist > maxdist)
            maxdist = dist, d = u;
        for (int i = head[u]; i; i = nxt[i])
        {
            int &v = to[i];
            if (v == fa) continue;
            dfs(v, u, dist + 1);
        }
    }
}

namespace old
{
    void dfs(int u, int fa, int bel)
    {
        for (int i = head[u]; i; i = nxt[i])
        {
            int &v = to[i];
            if (v == fa) continue;
            if (val[u] == val[v])
                dfs(v, u, bel);
            else
            {
                int _bel = ++after::tot;
                after::add(bel, _bel);
                after::add(_bel, bel);
                dfs(v, u, _bel);
            }
        }
    }
}

int main()
{
    old::n = read();
    FOR(i, 1, old::n)
        old::val[i] = read();
    FOR(i, 1, old::n - 1)
    {
        int u = read(), v = read();
        old::add(u, v);
        old::add(v, u);
    }
    old::dfs(1, 0, ++after::tot);
    after::dfs(1, 0, 0);
    after::maxdist = 0;
    after::dfs(after::d, 0, 0);
    printf("%d\n", (after::maxdist + 1) >> 1);
    return 0;
}
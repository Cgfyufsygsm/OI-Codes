#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

ll read()
{
    ll s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll min(ll a, ll b) {return a < b ? a : b;}

const int maxn = 200 + 5, maxm = 5000 * 2 + 5;
const ll inf = 1e18;

int head[maxn], cnt = 1, n, m, s, t;
int dep[maxn], cur[maxn];
int q[maxn << 1], qhead, qtail;

struct edge
{
    int to, nxt;
    ll w;
} e[maxm];

inline void add(int u, int v, ll w)
{
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

bool bfs()
{
    for (int i = 0; i <= n; ++i)
        cur[i] = head[i], dep[i] = -1;
    q[qhead = qtail = 1] = s;
    dep[s] = 0;
    while (qhead <= qtail)
    {
        int u = q[qhead++];
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (e[i].w > 0 && dep[v] == -1)
            {
                q[++qtail] = v;
                dep[v] = dep[u] + 1;
                if (v == t)
                    return 1;
            }
        }
    }
    return 0;
}

ll dfs(int u, ll in)
{
    if (u == t)
        return in;
    ll out = 0;
    for (int i = cur[u]; i; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].to;
        if (e[i].w > 0 && dep[v] == dep[u] + 1)
        {
            ll res = dfs(v, min(in, e[i].w));
            e[i].w -= res;
            e[i ^ 1].w += res;
            in -= res;
            out += res;
        }
        if (!in) break;
    }
    if (!out)
        dep[u] = -1;
    return out;
}

ll dinic()
{
    ll maxflow = 0;
    while (bfs())
        maxflow += dfs(s, inf);
    return maxflow;
}

int main()
{
    n = read(), m = read(), s = read(), t = read();
    FOR(i, 1, m)
    {
        int u = read(), v = read();
        ll w = read();
        add(u, v, w);
        add(v, u, 0);
    }
    printf("%lld\n", dinic());
    return 0;
}
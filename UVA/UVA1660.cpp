#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0;
    bool x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 1005, maxm = 1e4 + 5, inf = 1e9 + 7;
int head[maxn], cnt;
int s, t;
int dep[maxn], cur[maxn];

struct edge
{
    int to, nxt, w;
} e[maxm];


void add(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].w = 0;
    e[cnt].nxt = head[v];
    head[v] = cnt;
    return;
}

int q[maxn], qhead, qtail;

bool bfs()
{
    FOR(i, 0, 205)
        dep[i] = -1, cur[i] = head[i];
    q[qhead = qtail = 1] = s;
    dep[s] = 0;
    while (qhead <= qtail)
    {
        int u = q[qhead++];
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (dep[v] == -1 && e[i].w > 0)
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

int dfs(int u, int in)
{
    if (u == t)
        return in;
    int out = 0;
    for (int i = cur[u]; i; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].to;
        if (dep[v] == dep[u] + 1 && e[i].w)
        {
            int res = dfs(v, min(in, e[i].w));
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

int dinic()
{
    int ret = 0;
    while (bfs())
        ret += dfs(s, 1e9);
    return ret;
}

int n, m, a[maxm], b[maxm];

int main()
{
    while (~scanf("%d %d", &n, &m))
    {
        FOR(i, 1, m)
            a[i] = read() + 1, b[i] = read() + 1;
        int ans = inf;
        for (s = 1; s <= n; ++s)
            for (t = 1; t <= n; ++t)
            {
                if (s == t)
                    continue;
                memset(head, 0, sizeof head);
                cnt = 1;
                FOR(i, 1, n)
                    if (i == s || i == t)
                        add(i, i + n, inf);
                    else add(i, i + n, 1);
                FOR(i, 1, m)
                    add(a[i] + n, b[i], inf), add(b[i] + n, a[i], inf);
                int t = dinic();
                ans = min(ans, t);
            }
        if (n <= 1 || ans >= inf)
            ans = n;
        printf("%d\n", ans);
    }
    return 0;
}
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 205, maxm = 10200 * 4 + 5;

struct edge0
{
    int u, v, l, h, id;
} e0[maxm];

int n, m, a[maxn];//a 记录入-出

int head[maxn], cnt = 1, s, t;
int dep[maxn], cur[maxn];

struct edge
{
    int to, w, nxt;
} e[maxm];

void add(int u, int v, int w, int &id)
{
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    e[cnt].w = w;
    head[u] = cnt;
    id = cnt;
    e[++cnt].to = u;
    e[cnt].nxt = head[v];
    e[cnt].w = 0;
    head[v] = cnt;
    return;
}

int q[maxn], qhead, qtail;

bool bfs()
{
    FOR(i, 1, t)
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
    if (!out) dep[u] = -1;
    return out;
}

int dinic()
{
    int res = 0;
    while (bfs())
        res += dfs(s, 1e9);
    return res;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, m)
    {
        e0[i].u = read(), e0[i].v = read(), e0[i].l = read(), e0[i].h = read();
        a[e0[i].v] += e0[i].l, a[e0[i].u] -= e0[i].l;
        add(e0[i].u, e0[i].v, e0[i].h - e0[i].l, e0[i].id);
    }
    s = n + 1, t = n + 2;
    std::vector<int> tmp;
    FOR(i, 1, n)
    {
        int id;
        if (a[i] > 0)
            add(s, i, a[i], id), tmp.push_back(id);
        else if (a[i] < 0)
            add(i, t, -a[i], id);
    }
    dinic();
    FOR(i, 0, tmp.size() - 1)
        if (e[tmp[i]].w)
        {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");
    FOR(i, 1, m)
        printf("%d\n", e0[i].l + e[e0[i].id ^ 1].w);
    return 0;
}
#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 1e4 + 5, maxm = 1e6 + 5, inf = 1e9;

int n, s, t;
int head[maxn], cnt = 1;
int cur[maxn], dep[maxn];
int sta, ship, k;

struct edge
{
    int to, w, nxt;
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
    FOR(i, 0, n)
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

struct UnionFind
{
    int fa[25];
    il int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}
    il void uni(int u, int v) {fa[find(u)] = find(v); return;}
    il bool ask(int u, int v) {return find(u) == find(v);}
    UnionFind() {FOR(i, 1, 24) fa[i] = i;}
} uf;

int S[35][20], h[25], r[25];

il int node(int now, int day)
{
    if (now == -1) return t;
    else if (now == 0) return s;
    else return now + day * sta + 2;
}

int main()
{
    sta = read(), ship = read(), k = read();
    FOR(i, 1, ship)
    {
        h[i] = read(), r[i] = read();
        FOR(j, 1, r[i])
        {
            S[i][j] = read();
            if (j > 1)
                uf.uni(S[i][j] + 2, S[i][j - 1] + 2);
        }
    }
    if (!uf.ask(0 + 2, -1 + 2))
    {
        printf("0\n");
        return 0;
    }
    s = 1, t = 2, n = 2;
    int flow = 0;
    for (int day = 0; ; ++day)
    {
        n += sta;
        if (day > 0)
        {
            FOR(i, 1, sta)
                add(node(i, day - 1), node(i, day), inf);
            FOR(i, 1, ship)
            {
                int last = (day - 1) % r[i] + 1, cur = day % r[i] + 1;
                add(node(S[i][last], day - 1), node(S[i][cur], day), h[i]);
            }
        }
        flow += dinic();
        //printf("day %d flow %d\n", day, flow);
        if (flow >= k)
        {
            printf("%d\n", day);
            return 0;
        }
    }
    return 0;
}
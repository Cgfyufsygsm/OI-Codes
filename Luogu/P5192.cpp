#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define init(a) memset((a), 0, sizeof(a))

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

const int maxn = 2000 + 5, maxm = 8e5 + 5, inf = 2e9;

int head[maxn], cnt = 1;
int n;
int dep[maxn], cur[maxn], a[maxn];

void clear()
{
    init(head);
    init(a);
    cnt = 1;
}

struct edge
{
    int to, w, nxt;
} e[maxm];

void add(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    e[cnt].w = w;
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].nxt = head[v];
    e[cnt].w = 0;
    head[v] = cnt;
    return;
}

inline void add_(int u, int v, int l, int r)
{
    a[v] += l, a[u] -= l;
    add(u, v, r - l);
    return;
}

int q[maxn], qhead, qtail;

bool bfs(int s, int t)
{
    FOR(i, 1, n)
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

int dfs(int u, int in, int t)
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
            int res = dfs(v, min(in, e[i].w), t);
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

int dinic(int s, int t)
{
    int res = 0;
    while (bfs(s, t))
        res += dfs(s, inf, t);
    return res;
}

int main()
{
    int n_, m_, kase = 1;
    for (int kase = 1; ~scanf("%d %d", &n_, &m_); ++kase)
    {
        if (kase > 1)
        {
            clear();
            printf("\n");
        }
        n = 4 + n_ + m_;
        int s = n - 3, t = n - 2, ss = n - 1, tt = n;
        FOR(i, 1, m_)
            add_(n_ + i, t, read(), inf);
        FOR(i, 1, n_)
        {
            int c = read(), d = read();
            add_(s, i, 0, d);
            FOR(j, 1, c)
            {
                int t = read() + 1, l = read(), r = read();
                add_(i, n_ + t, l, r);
            }
        }
        int id_st, sum = 0;
        add(t, s, inf);
        id_st = cnt;
        FOR(i, 1, n)
        {
            if (a[i] > 0)
                add(ss, i, a[i]), sum += a[i];
            else if (a[i] < 0)
                add(i, tt, -a[i]);
        }
        if (dinic(ss, tt) != sum)
        {
            printf("-1\n");
            continue;
        }
        int flow1 = e[id_st].w;
        e[id_st].w = e[id_st ^ 1].w = 0;
        printf("%d\n", dinic(s, t) + flow1);
    }
    return 0;
}
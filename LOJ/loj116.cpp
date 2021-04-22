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

const int maxn = 200 + 7, maxm = 9999 * 4 + 5, inf = 1e9;


int n, m, a[maxn];//a 记录入-出

int head[maxn], cnt = 1, s, t, ss, tt;
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

bool bfs(int s, int t)
{
    FOR(i, 1, tt)
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
    n = read(), m = read(), s = read(), t = read();
    ss = n + 1, tt = n + 2;
    FOR(i, 1, m)
    {
        int u = read(), v = read(), l = read(), h = read(), tmp;
        a[u] -= l, a[v] += l;
        add(u, v, h - l, tmp);
    }
    int id_st;
    add(t, s, inf, id_st);
    FOR(i, 1, n)
    {
        int tmp;
        if (a[i] > 0)
            add(ss, i, a[i], tmp);
        else if (a[i] < 0)
            add(i, tt, -a[i], tmp);
    }
    dinic(ss, tt);
    for (int i = head[ss]; i; i = e[i].nxt)
        if (e[i].w)
        {
            printf("please go home to sleep\n");
            return 0;
        }
    int ans1 = e[id_st ^ 1].w;
    e[id_st].w = e[id_st ^ 1].w = 0;
    printf("%d\n", ans1 + dinic(s, t));
    return 0;
}
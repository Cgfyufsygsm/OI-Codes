#include <cstdio>
#include <cctype>
#include <cstring>
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

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 1500 + 5, maxm = 200000 + 5;

int head[maxn], cnt = 1;
int s, t, n;
int dep[maxn], cur[maxn];

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

int main()
{
    int kk = read(), nn = read();
    n = nn + kk + 2;
    //1 - nn 试题 nn + 1 - nn + kk 类型
    //nn + kk + 1 源 nn + kk + 2 汇
    s = nn + kk + 1, t = nn + kk + 2;
    int m = 0;
    FOR(i, nn + 1, nn + kk)
    {
        int tmp = read();
        add(i, t, tmp);
        m += tmp;
    }
    FOR(i, 1, nn)
    {
        int p = read();
        FOR(j, 1, p)
            add(i, read() + nn, 1);
        add(s, i, 1);
    }
    int maxf = dinic();
    if (maxf == m)
    {
        FOR(u, nn + 1, nn + kk)
        {
            printf("%d: ", u - nn);
            for (int i = head[u]; i; i = e[i].nxt)
                if (e[i].w && e[i].to <= n)
                    printf("%d ", e[i].to);
            printf("\n");
        }
    }
    else printf("No Solution!\nn");
    return 0;
}
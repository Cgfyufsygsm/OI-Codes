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

const int maxn = 1000, maxm = 200000;

int head[maxn], cnt = 1;
int s, t, n;
int dep[maxn], cur[maxn];
int eid[maxn][maxn];

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
    eid[u][v] = cnt;
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
        q[i] = 0, dep[i] = -1, cur[i] = head[i];
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
        int v = e[i].to;
        cur[u] = i;
        if (dep[v] == dep[u] + 1 && e[i].w)
        {
            int res = dfs(v, min(in, e[i].w));
            e[i].w -= res;
            e[i ^ 1].w += res;
            out += res;
            in -= res;
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
    int mm = read(), nn = read();
    //1 - m 单位，m + 1 - m + n 餐桌
    // m + n + 1:源点，m + n + 2: 汇点
    n = mm + nn + 2;
    s = mm + nn + 1, t = mm + nn + 2;
    int sumr = 0;
    FOR(i, 1, mm)
    {
        int tmp = read();
        add(s, i, tmp);
        sumr += tmp;
    }
    FOR(i, mm + 1, mm + nn)
        add(i, t, read());
    FOR(i, 1, mm)
        FOR(j, mm + 1, mm + nn)
            add(i, j, 1);
    int maxf = dinic();
    if (maxf == sumr)
    {
        printf("1\n");
        FOR(i, 1, mm)
        {
            FOR(j, mm + 1, mm + nn)
                if (e[eid[i][j]].w == 0)
                    printf("%d ", j - mm);
            printf("\n");
        }
    }
    else printf("0\n");
    return 0;
}
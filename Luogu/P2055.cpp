#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 505, maxm = 1e4 + 5;
int _n, s, t, goal;
int head[maxn], cnt = 1;
int dep[maxn], cur[maxn];
int home[maxn];//0 stay 1 go back -1 not in school

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
    //printf("add %d %d %d\n", u, v, w);
    return;
}

bool bfs()
{
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof head);
    std::queue<int> q;
    q.push(s), dep[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (dep[v] == -1 && e[i].w)
            {
                q.push(v);
                dep[v] = dep[u] + 1;
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int in)
{
    if (u == t) return in;
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
    int ret = 0;
    while (bfs()) ret += dfs(s, 1e9);
    return ret;
}

int main()
{
    int T = read();
    while (T--)
    {
        _n = read();
        goal = 0;
        s = _n * 2 + 1, t = s + 1;
        cnt = 1;
        memset(head, 0, sizeof head);
        FOR(i, 1, _n)
            if (!read())
                home[i] = -1;
            else home[i] = 0;
        FOR(i, 1, _n)
        {
            int tmp = read();
            if (home[i] != -1)
                home[i] = tmp;
            if (home[i] < 1) ++goal;
        }
        FOR(i, 1, _n)
            FOR(j, 1, _n)
                if (read() || i == j)
                    add(i, j + _n, 1);
        FOR(i, 1, _n)
        {
            if (home[i] < 1)
                add(s, i, 1);
            if (home[i] != -1)
                add(i + _n, t, 1);
        }
        //printf("%d\n", dinic());
        if (dinic() == goal)
            puts("^_^");
        else puts("T_T");
    }
    return 0;
}
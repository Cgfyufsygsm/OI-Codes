#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
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

const int maxn = 4000 + 5, maxm = 500000 + 5;

int s, t;
int head[maxn], cnt = 1;
int cur[maxn], dep[maxn];

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
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof head);
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

inline int nodein(int n) {return n * 2 + 1;}
inline int nodeout(int n) {return n * 2 + 2;}

inline bool isok(int n)
{
    int s = sqrt(n);
    return s * s == n;
}

bool vis[maxn];

int main()
{
    int _n = read(), ans = 0;
    s = 1, t = 2;
    int flow = 0, col = 0, now;
    for (now = 1;; ++now)
    {
        add(s, nodein(now), 1);
        add(nodeout(now), t, 1);
        FOR(i, 1, now - 1)
            if (isok(i + now))
                add(nodein(i), nodeout(now), 1);
        flow += dinic();
        col = now - flow;
        if (col > _n)
        {
            ans = --now;
            break; 
        }
    }
    printf("%d\n", ans);
    FOR(st, 1, now)
    {
        if (vis[st]) continue;
        bool flag = 1;
        int u = nodein(st);
        while (flag)
        {
            printf("%d ", (u - 1) / 2);
            vis[(u - 1) / 2] = 1;
            flag = 0;
            for (int i = head[u]; i; i = e[i].nxt)
                if (!e[i].w && !(e[i].to & 1) && e[i].to != t && (e[i].to - 2) / 2 <= now)
                {
                    u = nodein((e[i].to - 2) / 2);
                    flag = 1;
                    break;
                }
        }
        printf("\n");
    }
    return 0;
}
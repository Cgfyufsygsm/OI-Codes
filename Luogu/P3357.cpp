#include <cstdio>
#include <cctype>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define int long long

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

struct NetworkFlow
{
    static const int maxn = 2005, maxm = 10005, inf = 1e18;
    int head[maxn], cnt = 1;
    int inq[maxn], dis[maxn], flow[maxn], pre[maxn];
    int s, t;

    struct edge
    {
        int to, nxt, w, cost;
    } e[maxm];

    void add(int u, int v, int w, int c)
    {
        e[++cnt].to = v, e[cnt].w = w, e[cnt].cost = c, e[cnt].nxt = head[u], head[u] = cnt;
        e[++cnt].to = u, e[cnt].w = 0, e[cnt].cost = -c ,e[cnt].nxt = head[v], head[v] = cnt;
        //printf("added %d to %d\n", u, v);
        return;
    }

    bool SPFA()
    {
        memset(inq, 0, sizeof inq);
        memset(dis, 0xc0, sizeof dis);
        std::queue<int> q;
        q.push(s), inq[s] = 1, dis[s] = 0;
        flow[s] = inf;
        while (!q.empty())
        {
            int u = q.front(); q.pop(); inq[u] = 0;
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (e[i].w > 0 && e[i].cost + dis[u] > dis[v])
                {
                    dis[v] = dis[u] + e[i].cost;
                    flow[v] = min(flow[u], e[i].w);
                    pre[v] = i;
                    if (!inq[v])
                        q.push(v), inq[v] = 1;
                }
            }
        }
        return dis[t] > (int)0xc0c0c0c0c0c0c0c0;
    }

    int update()
    {
        int now = t;
        while (now != s)
        {
            int i = pre[now];
            e[i].w -= flow[t];
            e[i ^ 1].w += flow[t];
            now = e[i ^ 1].to;
        }
        return flow[t] * dis[t];
    }

    int solve()
    {
        int ret = 0;
        while (SPFA())
            ret += update();
        return ret;
    }
} MCMF;

const int maxn = 505;
int n, k;

std::map<int, int> point_id;
std::set<int> point;

struct node
{
    int len, l, r;
} s[maxn];

signed main()
{
    n = read(), k = read();
    FOR(i, 1, n)
    {
        int x0 = read(), y0 = read(), x1 = read(), y1 = read();
        s[i].len = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
        int l = x0 << 1, r = x1 << 1;
        if (l > r) std::swap(l, r);
        if (l == r) ++r;
        else ++l;
        s[i].l = l, s[i].r = r;
        point.insert(l), point.insert(r);
    }
    int cntp = 0;
    for (auto i : point)
        point_id[i] = ++cntp;
    MCMF.s = cntp + 1, MCMF.t = MCMF.s + 1;
    MCMF.add(MCMF.s, 1, k, 0), MCMF.add(cntp, MCMF.t, k, 0);
    FOR(i, 1, cntp - 1)
        MCMF.add(i, i + 1, MCMF.inf, 0);
    FOR(i, 1, n)
        MCMF.add(point_id[s[i].l], point_id[s[i].r], 1, s[i].len);
    printf("%lld\n", MCMF.solve());
    return 0;
}
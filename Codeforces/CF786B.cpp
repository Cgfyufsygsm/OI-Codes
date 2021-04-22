#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#define R register
#define FOR(i, a, b) for (R signed i = a; i <= b; ++i)
#define ls (k << 1)
#define rs (ls | 1)
#define M ((i + j) >> 1)
#define int long long

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

const int maxn = 1e5 + 5, INF = 0x3f3f3f3f3f3f3f3f;
int n, q, s, treeIn[maxn << 2], treeOut[maxn << 2], cnt;
bool vis[maxn * 10];

struct edge
{
    int to, nxt, dis;
} e[maxn * 30];

int cnte, head[maxn * 10], dis[maxn * 10];

void add(int u, int v, int w)
{
    e[++cnte].to = v;
    e[cnte].dis = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

void build(int i, int j, int k)
{
    if (i == j)
    {
        treeIn[k] = i, treeOut[k] = i;
        return;
    }
    build(i, M, ls);
    build(M + 1, j, rs);
    treeIn[k] = ++cnt, treeOut[k] = ++cnt;
    add(treeOut[ls], treeOut[k], 0);
    add(treeOut[rs], treeOut[k], 0);
    add(treeIn[k], treeIn[ls], 0);
    add(treeIn[k], treeIn[rs], 0);
    return;
}

void update(int opt, int i, int j, int k, int l, int r, int u, int dist)
{
    if (i >= l && j <= r)
    {
        if (opt == 2)
            add(u, treeIn[k], dist);
        else add(treeOut[k], u, dist);
        return;
    }
    if (l <= M)
        update(opt, i, M, ls, l, r, u, dist);
    if (r > M)
        update(opt, M + 1, j, rs, l, r, u, dist);
}

struct state
{
    int now, dist;
    state() {}
    state(int u, int w)
    {
        now = u, dist = w;
    }
    bool operator<(const state &b) const
    {
        return this->dist > b.dist;
    }
};

void dijkstra()
{
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0;
    std::priority_queue<state> q;
    q.push(state(s, 0));
    while (!q.empty())
    {
        int now = q.top().now;
        q.pop();
        if (!vis[now])
        {
            vis[now] = 1;
            for (signed i = head[now]; i; i = e[i].nxt)
            {
                int &to = e[i].to, &w = e[i].dis;
                if (dis[to] > dis[now] + w)
                {
                    dis[to] = dis[now] + w;
                    q.push(state(to, dis[to]));
                }
            }
        }
    }
    return;
}

signed main()
{
    cnt = n = read(), q = read(), s = read();
    build(1, n, 1);
    R int opt, _u, _v, _w, _l, _r;
    while (q--)
    {
        opt = read();
        if (opt == 1)
        {
            _u = read(), _v = read(), _w = read();
            add(_u, _v, _w);
        }
        else
        {
            _u = read(), _l = read(), _r = read(), _w = read();
            update(opt, 1, n, 1, _l, _r, _u, _w);
        }
    }
    dijkstra();
    FOR(i, 1, n)
        printf("%lld ", dis[i] == INF ? -1 : dis[i]);
    return 0;
}
#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>

typedef long long ll;

inline ll read()
{
    ll s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return s;
}

ll min(ll a, ll b) { return a < b ? a : b; }

const int maxn = 5e3 + 5, maxm = 5e4 + 5;
int head[maxn], to[maxm << 1], nxt[maxm << 1], cnt = 1;
int pre[maxn], inq[maxn];
ll w[maxm << 1], c[maxm << 1], flow[maxn], dis[maxn];
ll maxflow, mincost;
int n, m, s, t;

inline void add(int u, int v, ll _w, ll _c)
{
    to[++cnt] = v;
    w[cnt] = _w;
    c[cnt] = _c;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

bool spfa()
{
    memset(inq, 0, sizeof inq);
    memset(dis, 0x3f, sizeof dis);
    std::queue<int> q;
    q.push(s);
    inq[s] = 1, dis[s] = 0;
    flow[s] = 1e18;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int i = head[u]; i; i = nxt[i])
        {
            int v = to[i];
            if (w[i] > 0 && c[i] + dis[u] < dis[v])
            {
                dis[v] = c[i] + dis[u];
                flow[v] = min(w[i], flow[u]);
                pre[v] = i;
                if (!inq[v])
                {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f3f3f3f3f;
}

void update()
{
    int now = t;
    while (now != s)
    {
        int i = pre[now];
        w[i] -= flow[t];
        w[i ^ 1] += flow[t];
        now = to[i ^ 1];
    }
    maxflow += flow[t];
    mincost += flow[t] * dis[t];
    return;
}

int main()
{
    n = read(), m = read(), s = read(), t = read();
    while (m--)
    {
        int u = read(), v = read();
        ll w = read(), c = read();
        add(u, v, w, c);
        add(v, u, 0, -c);
    }
    while (spfa())
        update();
    printf("%lld %lld\n", maxflow, mincost);
    return 0;
}
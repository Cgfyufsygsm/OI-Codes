#include <cstdio>
#include <cctype>
#include <cstring>
#include <utility>
#include <queue>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

using namespace std;
typedef long long ll;

ll read()
{
    ll s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll max(ll a, ll b) {return a > b ? a : b;}
inline ll min(ll a, ll b) {return a < b ? a : b;}

const int maxn = 1e5 + 5, maxm = 5e5 + 5;
int n, m, k, s, t;
int vec[maxn];
int head[maxn], head0[maxn], to[maxm], nxt[maxm], cnt0, cnt;
ll w[maxm];

void add(int u, int v, ll dis)
{
    to[++cnt] = v;
    w[cnt] = dis;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

ll dijkstra(int s, int t)
{
    static ll dis[maxn];
    static int vis[maxn];
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (!vis[u])
        {
            vis[u] = 1;
            FOR(op, 0, 1)
                for (int i = head[u]; i; i = nxt[i])
                {
                    int v = to[i], d = w[i];
                    if (dis[u] + d < dis[v])
                    {
                        dis[v] = dis[u] + d;
                        q.push(make_pair(dis[v], v));
                    }
                }
        }
    }
    return dis[t];
}

int main()
{
    int T = read();
    while (T--)
    {
        cnt = 0;
        memset(head, 0, sizeof head);
        n = read(), m = read(), k = read();
        FOR(i, 1, m)
        {
            int x = read(), y = read();
            ll z = read();
            add(x, y, z);
        }
        s = n + 1, t = s + 1;
        FOR(i, 1, k)
            vec[i] = read();
        cnt0 = cnt;
        memcpy(head0, head, (sizeof head[0]) * (n + 3));
        ll ans = 1e18;
        for (int bit = 1; bit <= n; bit <<= 1)
        {
            if (bit != 1) memcpy(head, head0, (sizeof head[0]) * (n + 3));
            cnt = cnt0;
            FOR(i, 1, k)
                if (vec[i] & bit)
                    add(s, vec[i], 0);
                else add(vec[i], t, 0);
            ans = min(ans, dijkstra(s, t));
            cnt = cnt0;
            memcpy(head, head0, (sizeof head[0]) * (n + 3));
            FOR(i, 1, k)
                if (vec[i] & bit)
                    add(vec[i], s, 0);
                else add(t, vec[i], 0);
            ans = min(ans, dijkstra(t, s));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
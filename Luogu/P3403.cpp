#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using ll = unsigned long long;
using namespace std;

struct edge {
    ll to, w;
    edge(ll _v = 0, ll _w = 0) : to(_v), w(_w) {}
};

const int maxn = 1e5 + 5;
ll dis[maxn], sum[maxn];
vector<edge> G[maxn];
bool vis[maxn];

void dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
    dis[1] = 1, vis[1] = 1;
    q.push(make_pair(1, 1));
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        vis[u] = 1;
        for (auto &e : G[u]) {
            int v = e.to;
            if (dis[u] + e.w < dis[v]) {
                dis[v] = dis[u] + e.w;
                if (!vis[v]) q.push(make_pair(dis[v], v));
            }
        }
    }
    return;
}

int main() {
    int x, y, z;
    ll H;
    scanf("%llu %d %d %d", &H, &x, &y, &z);
    FOR(i, 0, z - 1) dis[i] = ULLONG_MAX;
    FOR(i, 0, z - 1) {
        G[i].push_back(edge((i + x) % z, x));
        G[i].push_back(edge((i + y) % z, y));
    }
    dijkstra();
    ll ans = 0;
    FOR(i, 0, z - 1) if (dis[i] <= H) ans += (H - dis[i]) / z + 1;
    printf("%llu\n", ans);
    return 0;
}
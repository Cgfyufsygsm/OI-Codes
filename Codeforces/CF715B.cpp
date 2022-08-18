#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

using ll = long long;
const int maxn = 1005, maxm = 10005;
vector<pair<int, int>> G[maxn];
int n, m, S, T, L, vis[maxn];
ll dis[2][maxn];

struct Edge {
    int u, v; ll w;
} e[maxm];

void Dijkstra0(ll (&dis)[maxn]) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[S] = 0, q.push({0, S});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &p : G[u]) {
            int v = p.first; ll w = e[p.second].w;
            if (!w) w = 1;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
    return;
}

void Dijkstra1(ll (&dis)[maxn], ll (&d)[maxn]) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[S] = 0, q.push({0, S});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &p : G[u]) {
            int v = p.first; ll &w = e[p.second].w;
            if (!w) w = max(1ll, L - d[T] - dis[u] + d[v]);
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
    return;
}

int main() {
    cin >> n >> m >> L >> S >> T;
    FOR(i, 1, m) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        G[e[i].u].emplace_back(e[i].v, i);
        G[e[i].v].emplace_back(e[i].u, i);
    }
    Dijkstra0(dis[0]);
    if (dis[0][T] > L) return puts("NO"), 0;
    Dijkstra1(dis[1], dis[0]);
    if (dis[1][T] != L) return puts("NO"), 0;
    puts("YES");
    FOR(i, 1, m) printf("%d %d %lld\n", e[i].u, e[i].v, e[i].w);
    return 0;
}
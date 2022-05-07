#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, head) for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to)

using namespace std;
using ll = long long;
const ll INF = 1e18;
const int maxn = 1005, maxm = 1e5 + 5;

int head[maxn], cnte = 1;
int n, m, s, t;

struct Edge {
    int to, nxt; ll w, c;
} e[maxm];

void add(int u, int v, ll w, ll c) {
    e[++cnte] = {v, head[u], w, c}, head[u] = cnte;
    e[++cnte] = {u, head[v], 0, -c}, head[v] = cnte;
    return;
}

ll minCost, maxFlow, flow[maxn], dis[maxn];
int pre[maxn], inq[maxn];

bool SPFA() {
    memset(dis, 0x3f, sizeof dis);
    memset(inq, 0, sizeof inq);
    queue<int> q;
    q.push(s), inq[s] = 1, dis[s] = 0, flow[s] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), inq[u] = 0;
        GO(u, head) {
            if (e[i].w && dis[u] + e[i].c < dis[v]) {
                dis[v] = dis[u] + e[i].c;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if (!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
    return dis[t] < 0x3f3f3f3f3f3f3f3f;
}

void update() {
    int u = t;
    while (u != s) {
        int i = pre[u];
        e[i].w -= flow[t], e[i ^ 1].w += flow[t];
        u = e[i ^ 1].to;
    }
    maxFlow += flow[t], minCost += flow[t] * dis[t];
    return;
}

int main() {
    cin >> n >> m;
    FOR(i, 1, n) {
        ll a; cin >> a;
        add(i, i + 1, INF - a, 0);
    }
    FOR(i, 1, m) {
        int l, r, c; cin >> l >> r >> c;
        add(l, r + 1, INF, c);
    }
    add(s = n + 2, 1, INF, 0), add(n + 1, t = n + 3, INF, 0);
    while (SPFA()) update();
    cout << minCost << endl;
    return 0;
}
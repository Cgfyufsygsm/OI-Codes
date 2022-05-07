#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, head) for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to)

using namespace std;
const int INF = 1e9;
const int maxn = 105, maxm = 1e5 + 5;
int head[maxn], cnte = 1;

struct Edge {
    int to, nxt, w;
} e[maxm];

void add(int u, int v, int w) {
    e[++cnte] = {v, head[u], w}, head[u] = cnte;
    e[++cnte] = {u, head[v], 0}, head[v] = cnte;
    return;
}

int dep[maxn], cur[maxn];

bool bfs(int s, int t) {
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof head);
    queue<int> q;
    q.push(s), dep[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        GO(u, head) {
            if (e[i].w > 0 && dep[v] == -1) {
                dep[v] = dep[u] + 1;
                q.push(v);
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int in, int t) {
    if (u == t) return in;
    int out = 0;
    GO(u, cur) {
        cur[u] = i;
        if (e[i].w > 0 && dep[v] == dep[u] + 1) {
            int res = dfs(v, min(in, e[i].w), t);
            in -= res, e[i].w -= res;
            out += res, e[i ^ 1].w += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}

int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) ans += dfs(s, INF, t);
    return ans;
}

int f[maxn];

int main() {
    int n; cin >> n;
    FOR(u, 1, n) {
        int k; cin >> k;
        while (k--) {
            int v; cin >> v;
            add(u, v, INF);
            ++f[u], --f[v];
        }
    }
    int S = n + 1, T = n + 2, s = n + 3, t = n + 4;
    FOR(u, 1, n) {
        add(s, u, INF), add(u, t, INF);
        if (f[u] > 0) add(u, T, f[u]);
        else if (f[u] < 0) add(S, u, -f[u]);
    }
    add(t, s, INF);
    dinic(S, T);
    int ans = e[cnte].w;
    cerr << ans << endl;
    e[cnte].w = e[cnte ^ 1].w = 0;
    ans -= dinic(t, s);
    cout << ans << endl;
    return 0;
}
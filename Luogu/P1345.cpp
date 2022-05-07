#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 505, maxm = 5005;

int n, m, s, t, c1, c2, head[maxn], cnte = 1;
struct Edge {
    int to, nxt, w;
} e[maxm];

void add(int u, int v, int w) {
    e[++cnte] = {v, head[u], w}, head[u] = cnte;
    e[++cnte] = {u, head[v], 0}, head[v] = cnte;
    return;
}

int dep[maxn], cur[maxn];

bool bfs() {
    static int q[maxn], qh, qt;
    memset(dep, -1, (t + 1) * sizeof(int));
    memcpy(cur, head, (t + 1) * sizeof(int));
    q[qh = qt] = s, dep[s] = 0;
    while (qh <= qt) {
        int u = q[qh++];
        for (int i = head[u]; i; i = e[i].nxt) {
            int &v = e[i].to;
            if (e[i].w > 0 && dep[v] == -1) {
                dep[v] = dep[u] + 1;
                q[++qt] = v;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int in) {
    if (u == t) return in;
    int out = 0;
    for (int i = cur[u]; i; i = e[i].nxt) {
        cur[u] = i;
        int &v = e[i].to;
        if (e[i].w && dep[v] == dep[u] + 1) {
            int res = dfs(v, min(in, e[i].w));
            in -= res, e[i].w -= res;
            out += res, e[i ^ 1].w += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}

int dinic() {
    int ans = 0;
    while (bfs()) ans += dfs(s, 1e9);
    return ans;
}

int main() {
    cin >> n >> m >> c1 >> c2;
    s = 2 * n + 1, t = 2 * n + 2;
    FOR(i, 1, n) add(i, i + n, 1);
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        add(u + n, v, 1e9), add(v + n, u, 1e9);
    }
    add(s, c1 + n, 1e9), add(c2, t, 1e9);
    cout << dinic() << endl;
    return 0;
}
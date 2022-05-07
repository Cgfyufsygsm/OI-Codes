#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, head) for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to)

using namespace std;
const int maxn = 505, maxm = 1e5 + 5;
int head[maxn], cnte = 1, n, m, s, t, p, q;

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
    q[qh = qt = 1] = s, dep[s] = 0;
    while (qh <= qt) {
        int u = q[qh++];
        GO(u, head) {
            if (e[i].w && dep[v] == -1) {
                q[++qt] = v, dep[v] = dep[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int in) {
    if (u == t) return in;
    int out = 0;
    GO(u, cur) {
        cur[u] = i;
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
    cin >> n >> p >> q;
    s = 401, t = 402;
    FOR(i, 1, p) add(s, i, 1);
    FOR(i, 1, q) add(i + 300, t, 1);
    FOR(i, 1, n) FOR(j, 1, p) {
        int c; cin >> c;
        if (c) add(j, i + 100, 1);
    }
    FOR(i, 1, n) add(i + 100, i + 200, 1);
    FOR(i, 1, n) FOR(j, 1, q) {
        int c; cin >> c;
        if (c) add(i + 200, j + 300, 1);
    }
    cout << dinic() << endl;
    return 0;
}
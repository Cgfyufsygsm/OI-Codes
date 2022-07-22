#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class MaxFlow {
  private:
    static const int maxn = 7e4 + 5, maxm = 2e6 + 5;
    int head[maxn], cnte;
    struct Edge {
        int to, nxt, w;
    } e[maxm];
    int dep[maxn], cur[maxn];
    bool bfs() {
        static int q[maxn], qh, qt;
        memset(dep, -1, sizeof dep);
        memcpy(cur, head, sizeof head);
        q[qh = qt = 1] = S, dep[S] = 0;
        while (qh <= qt) {
            int u = q[qh++];
            for (int i = head[u]; i; i = e[i].nxt) {
                int &v = e[i].to;
                if (e[i].w && dep[v] == -1) {
                    q[++qt] = v;
                    dep[v] = dep[u] + 1;
                    if (v == T) return true;
                }
            }
        }
        return false;
    }
    int dfs(int u, int in) {
        if (u == T) return in;
        int out = 0;
        for (int i = cur[u]; i; i = e[i].nxt) {
            int &v = e[i].to;
            cur[u] = i;
            if (e[i].w > 0 && dep[v] == dep[u] + 1) {
                int res = dfs(v, min(in, e[i].w));
                e[i].w -= res, e[i ^ 1].w += res;
                in -= res, out += res;
            }
            if (!in) break;
        }
        if (!out) dep[u] = -1;
        return out;
    }
  public:
    int S, T;
    MaxFlow() {
        memset(head, 0, sizeof head);
        cnte = 1;
    }
    il void addEdge(int u, int v, int w) {
        e[++cnte] = {v, head[u], w}, head[u] = cnte;
        e[++cnte] = {u, head[v], 0}, head[v] = cnte;
        return;
    }
    int solve() {
        int ret = 0;
        while (bfs()) ret += dfs(S, 1e9);
        return ret;
    }
} flow;

const int INF = 1e9;
int P, Q, R, D;
int id[55][55][55], tot;

int main() {
    ios::sync_with_stdio(false);
    cin >> P >> Q >> R >> D;
    flow.S = 1, flow.T = tot = 2;
    FOR(z, 1, R + 1) FOR(x, 1, P) FOR(y, 1, Q) id[x][y][z] = ++tot;
    FOR(z, 1, R + 1) {
        FOR(x, 1, P) FOR(y, 1, Q) {
            int v;
            if (z <= R) cin >> v;
            if (z == 1) flow.addEdge(flow.S, id[x][y][z], INF);
            if (z <= R) flow.addEdge(id[x][y][z], id[x][y][z + 1], v);
            if (z == R + 1) flow.addEdge(id[x][y][z], flow.T, INF);
            static const int fx[] = {1, -1, 0, 0};
            static const int fy[] = {0, 0, 1, -1};
            if (z > D) FOR(k, 0, 3) {
                int tx = x + fx[k], ty = y + fy[k];
                if (x < 1 || x > P || y < 1 || y > Q) continue;
                flow.addEdge(id[x][y][z], id[tx][ty][z - D], INF);
            }
        }
    }
    cout << flow.solve() << endl;
    return 0;
}
#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class MaxFlow {
  private:
    static const int maxn = 3005, maxm = 2e5 + 5;
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

class BoardPainting {
  private:
    int n, m, id[55][55], tot;
  public:
    int minimalSteps(vector<string> mp) {
        n = mp.size(), m = mp[0].size();
        flow.S = 1, flow.T = tot = 2;
        auto check = [&](const int &x, const int &y) -> int {
            if (x < 0 || x >= n || y < 0 || y >= m) return 1;
            return mp[x][y] != '#';
        };
        FOR(i, 0, n - 1) FOR(j, 0, m - 1) if (mp[i][j] == '#') {
            id[i][j] = ++tot;
            flow.addEdge(flow.S, id[i][j], check(i, j - 1) + check(i, j + 1));
            flow.addEdge(id[i][j], flow.T, check(i - 1, j) + check(i + 1, j));
        }
        FOR(i, 0, n - 1) FOR(j, 0, m - 1) if (mp[i][j] == '#') {
            static const int fx[] = {0, 0, 1, -1};
            static const int fy[] = {1, -1, 0, 0};
            FOR(k, 0, 3) {
                int x = i + fx[k], y = j + fy[k];
                if (!check(x, y)) flow.addEdge(id[i][j], id[x][y], 1);
            }
        }
        return flow.solve() >> 1;
    }
    BoardPainting() {
        memset(id, 0, sizeof id);
        tot = 0;
    }
};
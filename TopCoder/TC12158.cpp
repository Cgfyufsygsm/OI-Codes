#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class MaxFlow {
  private:
    static const int maxn = 1005, maxm = 2e5 + 5;
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

class SurroundingGame {
  private:
    int n, m, tot, id1[25][25], id2[25][25];
    static const int INF = 1e9;
    il int calc(char c) {
        if (isdigit(c)) return c - '0';
        else if (islower(c)) return c - 'a' + 10;
        else if (isupper(c)) return c - 'A' + 36;
        return -1;
    }
  public:
    int maxScore(vector<string> c, vector<string> b) {
        n = c.size(), m = c[0].size();
        flow.S = 1, flow.T = tot = 2;
        FOR(i, 0, n - 1) FOR(j, 0, m - 1) id1[i][j] = ++tot, id2[i][j] = ++tot;
        int ans = 0;
        FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
            const static int fx[] = {1, -1, 0, 0};
            const static int fy[] = {0, 0, 1, -1};
            auto check = [&](const int &x, const int &y) {return x >= 0 && x < n && y >= 0 && y < m;};
            ans += calc(b[i][j]);
            if ((i + j) & 1) {
                flow.addEdge(flow.S, id1[i][j], calc(c[i][j]));
                flow.addEdge(id1[i][j], id2[i][j], calc(b[i][j]));
                FOR(k, 0, 3) {
                    int x = i + fx[k], y = j + fy[k];
                    if (!check(x, y)) continue;
                    flow.addEdge(id1[i][j], id2[x][y], INF);
                }
            } else {
                flow.addEdge(id1[i][j], flow.T, calc(c[i][j]));
                flow.addEdge(id2[i][j], id1[i][j], calc(b[i][j]));
                FOR(k, 0, 3) {
                    int x = i + fx[k], y = j + fy[k];
                    if (!check(x, y)) continue;
                    flow.addEdge(id2[x][y], id1[i][j], INF);
                }
            }
        }
        return ans - flow.solve();
    }
};
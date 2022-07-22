#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class MaxFlow {
  private:
    static const int maxn = 205, maxm = 2e5 + 5;
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

class RatingProgressAward {
  private:
    int n, m;
    static const int INF = 1e9;
  public:
    int maximalProgress(vector<int> chg, vector<int> a, vector<int> b) {
        n = chg.size(), m = a.size();
        flow.S = 2 * n + 1, flow.T = flow.S + 1;
        int ans = 0;
        FOR(i, 1, n) {
            ans += max(chg[i - 1], 0);
            flow.addEdge(flow.S, i, max(chg[i - 1], 0));
            flow.addEdge(i + n, flow.T, max(chg[i - 1], 0));
            flow.addEdge(i, i + n, -min(chg[i - 1], 0));
        }
        FOR(i, 0, m - 1) {
            flow.addEdge(a[i] + 1, b[i] + 1, INF);
            flow.addEdge(a[i] + n + 1, b[i] + n + 1, INF);
        }
        return ans - flow.solve();
    }
};
#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class MaxFlow {
  private:
    static const int maxn = 2005, maxm = 2e5 + 5;
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

class FoxAndCity {
  private:
    int n, id[45][45], tot;
    static const int INF = 1e9;
    int calc(int a, int b) {return (a - b) * (a - b);}
  public:
    FoxAndCity() {
        memset(id, 0, sizeof id);
        tot = 0;
    }
    int minimalCost(vector<string> mp, vector<int> A) {
        flow.S = 1, flow.T = tot = 2;
        n = A.size();
        FOR(d, 0, n) FOR(i, 0, n - 1) id[i][d] = ++tot;
        flow.addEdge(flow.S, id[0][0], INF);
        flow.addEdge(id[0][n], flow.T, INF);
        FOR(i, 1, n - 1) flow.addEdge(id[0][i], id[0][i + 1], INF);
        FOR(i, 1, n - 1) {
            flow.addEdge(flow.S, id[i][0], INF);
            flow.addEdge(id[i][n], flow.T, INF);
            flow.addEdge(id[i][0], id[i][1], INF);
            FOR(j, 1, n - 1) flow.addEdge(id[i][j], id[i][j + 1], calc(A[i], j));
        }
        FOR(i, 0, n - 1) FOR(j, 0, n - 1) if (mp[i][j] == 'Y') {
            FOR(k, 0, n - 1) flow.addEdge(id[i][k + 1], id[j][k], INF);
        }
        return flow.solve();
    }
};
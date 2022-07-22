#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class MCMF {
  private:
    static const int maxn = 705, maxm = 1e5 + 5;

    struct Edge {
        int to, nxt, w, c;
    } e[maxm];
    int head[maxn], cnte;

    int dis[maxn], flow[maxn], maxFlow, minCost;
    int pre[maxn], inq[maxn];

    bool SPFA() {
        memset(dis, 0x80, sizeof dis);
        memset(inq, 0, sizeof inq);
        queue<int> q;
        q.push(S), inq[S] = 1, dis[S] = 0, flow[S] = 1e9;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to) {
                if (e[i].w > 0 && dis[v] < dis[u] + e[i].c) {
                    dis[v] = dis[u] + e[i].c;
                    flow[v] = min(flow[u], e[i].w);
                    pre[v] = i;
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        return dis[T] > -1e9;
    }

    void update() {
        int u = T;
        while (u != S) {
            int i = pre[u];
            e[i].w -= flow[T], e[i ^ 1].w += flow[T];
            u = e[i ^ 1].to;
        }
        maxFlow += flow[T], minCost += flow[T] * dis[T];
        return;
    }
  public:
    int S, T;
    il void addEdge(int u, int v, int w, int c) {
        e[++cnte] = {v, head[u], w, c}, head[u] = cnte;
        e[++cnte] = {u, head[v], 0, -c}, head[v] = cnte;
        return;
    }
    MCMF() {
        memset(head, 0, sizeof head);
        cnte = 1;
    }
    pair<int, int> solve() {
        while (SPFA()) update();
        return {maxFlow, minCost};
    }
} flow;

const int maxn = 505;
char s[maxn], t[maxn];
int n, m, X;

int main() {
    cin >> n;
    cin >> (s + 1);
    flow.S = 1, flow.T = n + 2;
    cin >> m;
    FOR(i, 1, m) {
        int w, len;
        cin >> (t + 1) >> w;
        len = strlen(t + 1);
        auto match = [&](const int &l, const int &r) {
            bool flg = 1;
            for (int i = l; i <= r; ++i) {
                flg &= (s[i] == t[i - l + 1]);
                if (!flg) break;
            }
            return flg;
        };
        for (int l = 1, r = len; r <= n; ++l, ++r) if (match(l, r))
            flow.addEdge(l, r + 1, 1, w);
    }
    cin >> X;
    FOR(i, 1, n + 1) flow.addEdge(i, i + 1, X, 0);
    cout << flow.solve().second << endl;
    return 0;
}
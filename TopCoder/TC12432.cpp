#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

class CurvyonRails {
  private:
    static const int maxn = 2005;
    int n, m, id1[28][28], id2[28][28], tot;
    int S, T, cnt, cnt2;

    struct Edge {
        int to, nxt, w, c;
    } e[50005];
    int head[maxn], cnte;

    il void addEdge(int u, int v, int w, int c) {
        e[++cnte] = {v, head[u], w, c}, head[u] = cnte;
        e[++cnte] = {u, head[v], 0, -c}, head[v] = cnte;
        return;
    }

    int dis[maxn], flow[maxn], maxFlow, minCost;
    int pre[maxn], inq[maxn];

    bool SPFA() {
        memset(dis, 0x3f, sizeof dis);
        memset(inq, 0, sizeof inq);
        queue<int> q;
        q.push(S), inq[S] = 1, dis[S] = 0, flow[S] = 1e9;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to) {
                if (e[i].w > 0 && dis[v] > dis[u] + e[i].c) {
                    dis[v] = dis[u] + e[i].c;
                    flow[v] = min(flow[u], e[i].w);
                    pre[v] = i;
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        return dis[T] < 1e9;
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
    CurvyonRails() {
        maxFlow = minCost = 0;
        cnt = cnt2 = tot = 0;
        cnte = 1;
        memset(id1, 0, sizeof id1);
        memset(id2, 0, sizeof id2);
    }
    int getmin(vector<string> field) {
        n = field.size(), m = field[0].size();
        S = 1, T = tot = 2;
        FOR(i, 0, n - 1) FOR(j, 0, m - 1) if (field[i][j] != 'w') {
            id1[i][j] = ++tot;
            id2[i][j] = ++tot;
        }
        FOR(i, 0, n - 1) FOR(j, 0, m - 1) if (id1[i][j]) {
            if ((i + j) & 1) {
                ++cnt2, ++cnt;
                addEdge(id1[i][j], T, 1, 0);
                addEdge(id2[i][j], T, 1, 0);
            } else {
                --cnt2, ++cnt;
                addEdge(S, id1[i][j], 1, 0);
                addEdge(S, id2[i][j], 1, 0);
                FOR(k, 0, 3) {
                    static const int fx[] = {0, 1, 0, -1};
                    static const int fy[] = {1, 0, -1, 0};
                    int x = i + fx[k], y = j + fy[k];
                    if (x < 0 || x >= n || y < 0 || y >= m || field[x][y] == 'w') continue;
                    if (k & 1) addEdge(id1[i][j], id2[x][y], 1, 0);
                    else addEdge(id2[i][j], id1[x][y], 1, 0);
                }
            }
            int cost = (field[i][j] == 'C');
            addEdge(id1[i][j], id2[i][j], 1, cost);
            addEdge(id2[i][j], id1[i][j], 1, cost);
        }
        if (cnt2) return -1;
        while (SPFA()) update();
        if (maxFlow != cnt) return -1;
        return minCost;
    }
};
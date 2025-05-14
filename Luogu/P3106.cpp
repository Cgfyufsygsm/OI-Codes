#include <bits/stdc++.h>

using namespace std;
const int maxn = 10005, maxm = 50005;

struct Edge {
  int to, nxt;
  int w[3];
} e[maxm];
int head[maxn], cnt, n, m;
int dis[3][maxn], vis[maxn];

void add(int u, int v, int p, int q) {
  e[++cnt].to = v;
  e[cnt].nxt = head[u];
  e[cnt].w[0] = p;
  e[cnt].w[1] = q;
  head[u] = cnt;
  return;
}

void dijkstra(int s, int k) {
  memset(dis[k], 0x3f, sizeof dis[k]);
  memset(vis, 0, sizeof vis);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int> > > q;
  dis[k][s] = 0, q.push({0, s});
  while (!q.empty()) {
    int u = q.top().second; q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
      int &v = e[i].to;
      if (dis[k][v] > dis[k][u] + e[i].w[k]) {
        dis[k][v] = dis[k][u] + e[i].w[k];
        q.push({dis[k][v], v});
      }
    }
  }
  return;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v, p, q; cin >> u >> v >> p >> q;
    add(v, u, p, q);
  }
  dijkstra(n, 0), dijkstra(n, 1);
  for (int u = 1; u <= n; ++u) {
    for (int i = head[u]; i; i = e[i].nxt) {
      int &v = e[i].to;
      for (int k = 0; k < 2; ++k)
        if (dis[k][v] - dis[k][u] != e[i].w[k])
          ++e[i].w[2];
    }
  }
  dijkstra(n, 2);
  printf("%d\n", dis[2][1]);
  return 0;
}
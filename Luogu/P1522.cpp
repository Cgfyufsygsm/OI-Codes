#include <bits/stdc++.h>

using namespace std;
using db = double;
const int maxn = 155;
int n, posx[maxn], posy[maxn];
db dis[maxn][maxn], maxd[maxn], diam[maxn];

struct UnionFind {
  int fa[maxn], n;
  void init(int _n) {
    n = _n;
    for (int i = 1; i <= n; ++i) fa[i] = i;
  }
  int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y;
    return;
  }
  bool query(int x, int y) {return find(x) == find(y);}
} dsu;

db calcDis(int i, int j) {
  return sqrt((posx[i] - posx[j]) * (posx[i] - posx[j]) + (posy[i] - posy[j]) * (posy[i] - posy[j]));
}

int main() {
  cin >> n; dsu.init(n);
  for (int i = 1; i <= n; ++i) cin >> posx[i] >> posy[i];
  for (int i = 1; i <= n; ++i) {
    char str[maxn];
    cin >> (str + 1);
    for (int j = 1; j <= n; ++j) {
      dis[i][j] = 1e18;
      if (str[j] == '1') dis[i][j] = calcDis(i, j), dsu.merge(i, j);
    }
  }
  for (int k = 1; k <= n; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j)
      if (i != j && dsu.query(i, j))
        maxd[i] = max(maxd[i], dis[i][j]);
    diam[dsu.find(i)] = max(diam[dsu.find(i)], maxd[i]);
  }
  db ans = 1e18;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (!dsu.query(i, j))
    ans = min(ans, max(maxd[i] + maxd[j] + calcDis(i, j), max(diam[dsu.find(i)], diam[dsu.find(j)])));
  printf("%.6lf\n", ans);
  return 0;
}
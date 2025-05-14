#include <bits/stdc++.h>

using namespace std;

const int maxn = 505;
int n, m, w;
int f[maxn][maxn];

void solve() {
  cin >> n >> m >> w;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) f[i][j] = 0x3f3f3f3f;
  while (m--) {
    int u, v, p; cin >> u >> v >> p;
    f[u][v] = f[v][u] = min(f[u][v], p);
  }
  while (w--) {
    int u, v, p; cin >> u >> v >> p;
    f[u][v] = min(f[u][v], -p);
  }
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j)
        if (f[i][k] + f[k][j] < f[i][j])
          f[i][j] = f[i][k] + f[k][j];
      if (f[i][i] < 0) {
        puts("YES");
        return;
      }
    }
  puts("NO");
  return;
}

int main() {
  int T; cin >> T;
  while (T--) solve();
  return 0;
}
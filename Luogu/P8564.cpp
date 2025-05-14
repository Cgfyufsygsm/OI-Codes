#include <bits/stdc++.h>

using namespace std;

const int maxn = 5005;
using ll = long long;
int n; ll v[maxn], f[maxn][maxn], g[maxn];
int size[maxn];
vector<int> G[maxn];

void dfs(int u, int fa) {
  size[u] = 1;
  f[u][1] = 0;
  for (int v : G[u]) if (v != fa) {
    dfs(v, u);
    memset(g, 0x3f, sizeof(ll) * (size[u] + size[v] + 1));
    for (int j = 0; j <= size[u]; ++j)
      for (int k = 0; k <= size[v]; ++k)
        g[j + k] = min(g[j + k], f[u][j] + f[v][k]);
    memcpy(f[u], g, sizeof(ll) * (size[u] + size[v] + 1));
    size[u] += size[v];
  }
  f[u][size[u]] = 0;
  for (int i = 1; i <= size[u]; ++i) f[u][1] = min(f[u][1], f[u][i] + v[i]);
  return;
}

int main() {
  cin >> n;
  for (int i = 2; i <= n; ++i) cin >> v[i];
  for (int i = 2; i <= n; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  memset(f, 0x3f, sizeof f);
  dfs(1, 0);
  cout << f[1][1] << endl;
  return 0;
}
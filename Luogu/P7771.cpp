#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
int n, m, stk[maxm], top, ind[maxn], oud[maxn];
vector<int> G[maxn]; // 里面存边的编号
int head[maxn];

void dfs(int u) {
  for (int i = head[u]; i < (int)G[u].size(); i = head[u]) {
    head[u] = i + 1;
    dfs(G[u][i]);
  }
  stk[++top] = u;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    G[u].push_back(v), ++ind[v], ++oud[u];
  }
  int S = 1;
  for (int i = 1; i <= n; ++i)
    if (!G[i].empty())
      sort(G[i].begin(), G[i].end());
  int cnt[2] = {0, 0};
  for (int i = 1; i <= n; ++i) {
    if (oud[i] != ind[i]) {
      if (oud[i] - ind[i] == 1) {
        S = i;
        ++cnt[0];
      } else if (ind[i] - oud[i] == 1) {
        ++cnt[1];
      } else {
        printf("No");
        return 0;
      }
    }
  }
  if ((cnt[0] || cnt[1]) && (cnt[0] != 1 || cnt[1] != 1)) {
    printf("No");
    return 0;
  }
  dfs(S);
  while (top) printf("%d ", stk[top--]);
  return 0;
}
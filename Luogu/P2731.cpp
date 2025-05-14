#include <bits/stdc++.h>

using namespace std;
const int maxn = 505, maxm = 4005;
struct Edge {
  int to; bool flg;
} e[maxm];
int cnt = 1, m, stk[maxm], top, deg[maxn];
vector<int> G[maxn]; // 里面存边的编号

void dfs(int u) {
  for (int i : G[u]) {
    if (e[i].flg) continue;
    e[i].flg = e[i ^ 1].flg = 1;
    dfs(e[i].to);
  }
  stk[++top] = u;
}

int main() {
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    e[++cnt] = {v, 0}, G[u].push_back(cnt), ++deg[v];
    e[++cnt] = {u, 0}, G[v].push_back(cnt), ++deg[u];
  }
  int S = 501;
  for (int i = 1; i <= 500; ++i)
    if (deg[i])
      sort(G[i].begin(), G[i].end(), [](int a, int b) {return e[a].to < e[b].to;});
  for (int i = 1; i <= 500; ++i) {
    if (deg[i]) {
      S = min(S, i);
      if (deg[i] & 1) {
        S = i;
        break;
      }
    }
  }
  dfs(S);
  while (top) printf("%d\n", stk[top--]);
  return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int maxm = 105;
int n, m, mp[maxm][maxm], val[maxm][maxm];

struct Node {
  int x, y, col, val;
};

const int fx[] = {0, 0, 1, -1};
const int fy[] = {1, -1, 0, 0};

int main() {
  memset(mp, -1, sizeof mp);
  cin >> m >> n;
  for (int i = 1; i <= n; ++i) {
    int x, y;
    cin >> x >> y;
    cin >> mp[x][y];
  }
  memset(val, 0x3f, sizeof val);
  queue<Node> q;
  q.push({1, 1, mp[1][1], 0});
  val[1][1] = 0;
  while (!q.empty()) {
    auto u = q.front();
    int x = u.x, y = u.y, col = u.col, v = u.val;
    q.pop();
    for (int k = 0; k < 4; ++k) {
      int tx = u.x + fx[k], ty = u.y + fy[k];
      if (tx < 1 || tx > m || ty < 1 || ty > m) continue;
      if (mp[x][y] == -1 && mp[tx][ty] == -1) continue;
      else if (mp[tx][ty] == -1 && v + 2 < val[tx][ty]) {
        val[tx][ty] = v + 2;
        q.push({tx, ty, col, v + 2});
      } else if (mp[tx][ty] != -1 && mp[tx][ty] == col && v < val[tx][ty]) {
        val[tx][ty] = v;
        q.push({tx, ty, col, v});
      } else if (mp[tx][ty] != -1 && mp[tx][ty] != col && v + 1 < val[tx][ty]) {
        val[tx][ty] = v + 1;
        q.push({tx, ty, mp[tx][ty], v + 1});
      }
    }
  }
  if (val[m][m] == 0x3f3f3f3f) cout << -1 << endl;
  else cout << val[m][m] << endl;
  return 0;
}
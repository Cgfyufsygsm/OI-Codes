#include <bits/stdc++.h>

using namespace std;

long long f[105][105][105];
int n, k, d, a[105];

int main() {
  cin >> n >> k >> d;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  memset(f, 0x80, sizeof f);
  f[0][0][0] = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= min(i, k); ++j)
      for (int l = 0; l < d; ++l) {
        f[i][j][l] = max(f[i][j][l], f[i - 1][j][l]);
        if (j) f[i][j][l] = max(f[i][j][l], f[i - 1][j - 1][((l - a[i]) % d + d) % d] + a[i]);
      }
  if (f[n][k][0] < 0) cout << -1 << endl;
  else cout << f[n][k][0] << endl;
  return 0;
}
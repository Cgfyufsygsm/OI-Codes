#include <bits/stdc++.h>

using namespace std;

const int maxn = 505;

char s[maxn];
int f[maxn][maxn], n;

int main() {
  cin >> n >> (s + 1);
  for (int len = 2; len <= n; ++len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int j = i + len - 1;
      f[i][j] = f[i + 1][j];
      for (int k = i + 1; k <= j; ++k) if (s[i] == s[k]) {
        f[i][j] = max(f[i][j], f[i + 1][k - 1] + f[k][j] + 1);
      }
    }
  }
  cout << n - f[1][n] << '\n';
  return 0;
}
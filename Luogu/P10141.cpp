#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int qPow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1)
            ans = 1ll * ans * a % mod;
    return ans;
}

const int maxn = 5005;
int n, a[maxn], f[maxn][maxn];
long long sum[maxn];

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
  }
  f[1][n] = 1;
  for (int len = n; len; --len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int j = i + len - 1;
      for (int k = i; k < j; ++k) {
        if (sum[k] - sum[i - 1] > sum[j] - sum[k])
          f[i][k] = (f[i][k] + 1ll * f[i][j] * qPow(j - i, mod - 2) % mod) % mod;
        else f[k + 1][j] = (f[k + 1][j] + 1ll * f[i][j] * qPow(j - i, mod - 2) % mod) % mod;
      }
    }
  }
  for (int i = 1; i <= n; ++i) cout << f[i][i] << endl;
  return 0;
}
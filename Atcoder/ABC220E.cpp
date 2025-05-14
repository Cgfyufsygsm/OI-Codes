#include <bits/stdc++.h>

using namespace std;
const int mod = 998244353;

int qPow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1ll * res * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return res;
}

int main() {
  int n, d; cin >> n >> d;
  int ans = 0;
  for (int l = 0; l <= d; ++l) {
    int r = d - l;
    if (max(l, r) >= n) continue;
    int root = (qPow(2, n - max(l, r)) + mod - 1) % mod;
    int L = qPow(2, max(0, l - 1));
    int R = qPow(2, max(0, r - 1));
    ans = (ans + 2ll * root % mod * L % mod * R % mod) % mod;
  }
  cout << ans << endl;
  return 0;
}
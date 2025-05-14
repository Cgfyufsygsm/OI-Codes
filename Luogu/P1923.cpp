#include <bits/stdc++.h>

using namespace std;

const int maxn = 5000005;

int n, k, a[maxn];

void qs(int l, int r) {
  int i = l, j = r, x = a[(l + r) >> 1];
  while (i <= j) {
    while (i <= j && a[i] < x) ++i;
    while (i <= j && a[j] > x) --j;
    if (i <= j) swap(a[i++], a[j--]);
  }
  if (k <= j) qs(l, j);
  else if (k >= i) qs(i, r);
  else {
    cout << a[i] << endl;
    exit(0);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  qs(1, n);
  return 0;
}
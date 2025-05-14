#include <bits/stdc++.h>

using namespace std;

const int maxn = 8005;

int rk[maxn], n, q;
struct Node {
  int val, id;
} b[maxn];

bool operator<(const Node &a, const Node &b) {
  return a.val == b.val ? a.id < b.id : a.val < b.val;
}

void bub(int p, int v) {
  b[p].val = v;
  while (p > 1 && b[p] < b[p - 1]) rk[b[p - 1].id]++, swap(b[p], b[p - 1]), --p;
  while (p < n && b[p + 1] < b[p]) rk[b[p + 1].id]--, swap(b[p], b[p + 1]), ++p;
  rk[b[p].id] = p;
}

int main() {
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> b[i].val;
    b[i].id = i;
  }
  sort(b + 1, b + n + 1);
  for (int i = 1; i <= n; ++i) rk[b[i].id] = i;
  while (q--) {
    int op, x, v;
    cin >> op;
    if (op == 1) {
      cin >> x >> v;
      bub(rk[x], v);
    } else {
      cin >> x;
      cout << rk[x] << endl;
    }
  }
}
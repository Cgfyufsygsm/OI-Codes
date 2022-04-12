#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;

using ll = long long;
const int maxn = 2e5 + 5;
int n, st[20][maxn << 1];

struct Node {
    ll val; int id;
} a[maxn << 1];

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i].val, a[i].id = i;
    sort(a + 1, a + n + 1, [](const Node &a, const Node &b) {return a.val > b.val;});
    ll sum = 0;
    FOR(i, 1, n >> 1) sum += a[i].val, a[i].val = 1;
    FOR(i, (n >> 1) + 1, n) a[i].val = -1;
    sort(a + 1, a + n + 1, [](const Node &a, const Node &b) {return a.id < b.id;});
    FOR(i, 1, n) a[n + i] = a[i];
    FOR(i, 1, n << 1) st[0][i] = st[0][i - 1] + a[i].val;
    FOR(j, 1, 19) FOR(i, 1, (n << 1) - (1 << j) + 1) st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    const int s = 31 - __builtin_clz(n);
    FOR(i, 1, n) if (a[i].val == 1) {
        int ret = max(st[s][i], st[s][i + n - (1 << s)]);
        if (ret <= st[0][i]) return cout << i - 1 << ' ' << sum << endl, 0;
    }
    return 0;
}
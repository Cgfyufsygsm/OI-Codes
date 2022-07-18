#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e6 + 5;
vector<tuple<int, int, int>> ans;
int l, r, n;

int main() {
    cin >> l >> r;
    r = r - l + 1;
    int k = 31 - __builtin_clz(r);
    n = k + 2;
    FOR(i, 0, k) FOR(j, i + 1, k) ans.emplace_back(i + 2, j + 2, 1 << i);
    FOR(i, 0, k) ans.emplace_back(1, i + 2, 1);
    if (__builtin_popcount(r) > 1) {
        --r, ans.emplace_back(1, ++n, 1);
        FOR(i, 0, k) if ((1 << i) & r) {
            int tmp = 0;
            FOR(j, i + 1, k) tmp |= ((1 << j) & r);
            ans.emplace_back(i + 2, n, 1 + tmp);
        }
    }
    if (l != 1) ans.emplace_back(n, n + 1, l - 1), ++n;
    cout << "YES\n" << n << ' ' << ans.size() << endl;
    for (auto &x : ans) {
        int i, j, k; tie(i, j, k) = x;
        cout << i << ' ' << j << ' ' << k << endl;
    }
    return 0;
}
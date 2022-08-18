#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define lowbit(x) (x & -x)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5, N = 2e5;
ll ans[maxn], d[maxn], t[maxn];
vector<pair<int, int>> q[maxn];

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    FOR(i, 1, T) {
        int l, r; cin >> l >> r;
        q[l].emplace_back(r, i);
    }
    auto add = [](int x, ll v) {for (; x <= N; x += lowbit(x)) t[x] += v;};
    auto query = [](int x) {ll ret = 0; for (; x; x -= lowbit(x)) ret += t[x]; return ret;};
    DEC(i, N, 1) {
        for (int j = i << 1; j <= N; j += i) {
            if (d[j]) add(j, d[j]);
            ++d[j];
        }
        if (i % 3 == 0 && i * 2 <= N) add(i * 2, 1);
        if (i % 6 == 0 && i / 2 * 5 <= N) add(i / 2 * 5, 1);
        for (auto &p : q[i]) {
            ll len = p.first - i + 1;
            ans[p.second] = len * (len - 1) * (len - 2) / 6 - query(p.first);
        }
    }
    FOR(i, 1, T) cout << ans[i] << '\n';
    return 0;
}
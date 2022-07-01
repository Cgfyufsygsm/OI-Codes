#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 105, maxm = 2e5 + 5;
ll v[maxn], ansF, ansL;
int n, m, tmp[maxn];

void solve(int s) {
    FOR(i, 1, n) tmp[i] = v[i] % s;
    tmp[0] = 0, tmp[n + 1] = s - 1;
    sort(tmp, tmp + n + 2);
    FOR(i, 1, n + 1) {
        bool fl = (n + 1 - i) & 1;
        int l = max(tmp[i - 1], tmp[n - 1 + (!fl)] / 2) + 1, r = min(tmp[i], m);
        (fl ? ansF : ansL) += max(0, min(r, s - l) - max(l, s - r) + 1);
    }
    return;
}

int main() {
    cin >> n >> m;
    FOR(i, 1, n) cin >> v[i];
    FOR(x, 2, m << 1) solve(x);
    ll ans1 = (1ll * m * m - ansL - ansF) >> 1;
    cout << ans1 << ' ' << ans1 << ' ' << ansF << ' ' << ansL << endl;
    return 0;
}
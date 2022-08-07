#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 3e5 + 5;
ll sum[maxn];
int n, m;

void solve() {
    cin >> n >> m;
    FOR(i, 1, n) {
        sum[i] = 0;
        FOR(j, 1, m) {
            ll a; cin >> a;
            sum[i] += a * j;
        }
    }
    auto mxv = max_element(sum + 1, sum + n + 1);
    cout << mxv - sum << ' ' << *mxv - *min_element(sum + 1, sum + n + 1) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
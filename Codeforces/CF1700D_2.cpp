#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 2e5 + 5;
using ll = long long;
using namespace std;
int n, q;
ll v[maxn], pre[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) cin >> v[i], pre[i] = v[i] + pre[i - 1];
    ll ddl = 0;
    FOR(i, 1, n) ddl = max(ddl, (pre[i] + i - 1) / i);
    cin >> q;
    while (q--) {
        int t; cin >> t;
        cout << (t < ddl ? -1 : (pre[n] + t - 1) / t) << '\n';
    }
    return 0;
}
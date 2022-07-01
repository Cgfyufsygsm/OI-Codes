#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 5e4 + 5;
int n, m, k, a[maxn], b[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        vector<pair<ll, ll>> va, vb;
        FOR(i, 1, n) {
            cin >> a[i];
            ll cnt = 1;
            while (a[i] % k == 0) cnt *= k, a[i] /= k;
            if (!va.empty() && va.back().first == a[i]) va.back().second += cnt;
            else va.push_back({a[i], cnt});
        }
        cin >> m;
        FOR(i, 1, m) {
            cin >> b[i];
            ll cnt = 1;
            while (b[i] % k == 0) cnt *= k, b[i] /= k;
            if (!vb.empty() && vb.back().first == b[i]) vb.back().second += cnt;
            else vb.push_back({b[i], cnt});
        }
        cout << (va == vb ? "YES" : "NO") << '\n';
    }
    return 0;
}
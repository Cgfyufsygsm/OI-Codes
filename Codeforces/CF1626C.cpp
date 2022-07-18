#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using ll = long long;
const int maxn = 105;
int n;
ll k[maxn], h[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> k[i];
        FOR(i, 1, n) cin >> h[i];
        ll ans = 0;
        DEC(i, n - 1, 1) h[i] = max(h[i], h[i + 1] - (k[i + 1] - k[i]));
        FOR(i, 1, n) {
            ll th = h[i - 1] + k[i] - k[i - 1];
            if (k[i] - k[i - 1] >= h[i]) ans += (h[i] + 1) * h[i] / 2;
            else h[i] = th, ans += (h[i] + h[i - 1] + 1) * (k[i] - k[i - 1]) / 2;
        }
        cout << ans << '\n';
    }
    return 0;
}
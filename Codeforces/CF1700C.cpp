#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
int n;
ll a[maxn], d[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i], d[i] = a[i] - a[i - 1];
        ll tmp = 0, ans = 0;
        FOR(i, 2, n) {
            if (d[i] < 0) tmp += -d[i];
            else ans += d[i];
        }
        ans += tmp;
        if (tmp > d[1]) ans += tmp - d[1];
        else ans += d[1] - tmp;
        cout << ans << '\n';
    }
    return 0;
}
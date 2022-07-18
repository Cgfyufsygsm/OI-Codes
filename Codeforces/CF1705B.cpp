#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
int n, a[maxn];

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        queue<int> zero;
        FOR(i, 1, n) {
            cin >> a[i];
            if (!a[i] && i != n) zero.push(i);
        }
        ll ans = 0;
        FOR(i, 1, n - 1) {
            if (!a[i]) continue;
            while (a[i] && !zero.empty()) {
                while (!zero.empty() && zero.front() <= i) zero.pop();
                if (zero.empty()) break;
                ++a[zero.front()], --a[i], ++ans;
                zero.pop();
            }
            ans += a[i];
        }
        cout << ans << endl;
    }
    return 0;
}
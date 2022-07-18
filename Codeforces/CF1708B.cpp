#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
int n, l, r, ans[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> l >> r;
        int cur = l, flg = 1;
        FOR(i, 1, n) {
            cur = (l + i - 1) / i * i;
            if (cur > r) {
                flg = 0;
                break;
            }
            ans[i] = cur;
        }
        if (!flg) cout << "NO\n";
        else {
            cout << "YES\n";
            FOR(i, 1, n) cout << ans[i] << ' ';
            cout << '\n';
        }
    }
    return 0;
}
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> X, Y;
        FOR(i, 1, n) {
            int x, y; cin >> x >> y;
            if (!x) Y.emplace_back(y);
            if (!y) X.emplace_back(x);
        }
        sort(X.begin(), X.end()), sort(Y.begin(), Y.end());
        int ans = 0;
        if (!X.empty() &&X.front() < 0) ans += -2 * X.front();
        if (!X.empty() && X.back() > 0) ans += 2 * X.back();
        if (!Y.empty() && Y.front() < 0) ans += -2 * Y.front();
        if (!Y.empty() && Y.back() > 0) ans += 2 * Y.back();
        cout << ans << '\n';
    }
    return 0;
}
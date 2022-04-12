#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        map<int, int> mp;
        FOR(i, 1, n) {
            int x; cin >> x;
            ++mp[x];
        }
        int maxt = 0, ans = 0;
        for (auto &p : mp) maxt = max(maxt, p.second);
        while (n - maxt > 0) {
            ++ans;
            ans += min(maxt, n - maxt);
            maxt *= 2;
        }
        cout << ans << '\n';
    }
    return 0;
}
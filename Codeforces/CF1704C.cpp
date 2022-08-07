#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
int n, m, a[maxn];

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        FOR(i, 1, m) cin >> a[i];
        sort(a + 1, a + m + 1);
        vector<int> vec;
        a[m + 1] = a[1] + n;
        FOR(i, 2, m + 1) vec.push_back(a[i] - a[i - 1] - 1);
        sort(vec.begin(), vec.end(), greater<int>());
        int t = 0, ans = m;
        for (int x : vec) {
            int tmp = min(2 * t, x);
            x -= tmp, ans += tmp;
            if (x >= 2) ++ans, t += 2;
            else if (x == 1) ++t;
        }
        cout << ans << '\n';
    }
    return 0;
}
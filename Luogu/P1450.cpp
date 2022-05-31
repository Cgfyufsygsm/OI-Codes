#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
ll f[maxn], c[5], n;

int main() {
    cin >> c[1] >> c[2] >> c[3] >> c[4] >> n;
    f[0] = 1;
    FOR(j, 1, 4) FOR(i, 0, 100000) if (i >= c[j]) f[i] += f[i - c[j]];
    while (n--) {
        ll d[5], s, ans = 0;
        cin >> d[1] >> d[2] >> d[3] >> d[4] >> s;
        FOR(state, 1, 15) {
            ll curs = s;
            FOR(i, 1, 4) if ((1 << (i - 1)) & state) curs -= (d[i] + 1) * c[i];
            if (curs >= 0) (__builtin_popcount(state) & 1) ? ans += f[curs] : ans -= f[curs];
        }
        cout << f[s] - ans << endl;
    }
    return 0;
}
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;

int main() {
    int T; cin >> T;
    while (T--) {
        ll hc, dc, hm, dm, k, w, a;
        cin >> hc >> dc >> hm >> dm;
        cin >> k >> w >> a;
        bool flg = 0;
        FOR(i, 0, k) { // 选多少次加自己生命
            ll hc2 = hc + i * a, dc2 = dc + (k - i) * w;
            flg |= ((hm + dc2 - 1) / dc2 <= (hc2 + dm - 1) / dm);
        }
        cout << (flg ? "YES" : "NO") << '\n';
    }
    return 0;
}
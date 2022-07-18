#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}

int main() {
    int T; cin >> T;
    while (T--) {
        int x, y, up; cin >> x >> y, up = sqrt(x);
        chkmin(y, x - 1);
        ll ans = 0;
        FOR(k, 1, up)
            ans += min(max(0, y - k), max(0, x / k - k - 1));
        cout << ans << endl;
    }
    return 0;
}
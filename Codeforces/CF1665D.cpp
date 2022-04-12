#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

il int ask(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    int ret; cin >> ret;
    return ret;
}

void solve() {
    int ans = 0;
    FOR(i, 1, 30) {
        int tmp = ask((1 << (i - 1)) - ans, (1 << i) + (1 << (i - 1)) - ans);
        ans += (tmp == (1 << i)) ? (1 << (i - 1)) : 0;
    }
    cout << "! " << ans << endl;
    return;
}

int main() {
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
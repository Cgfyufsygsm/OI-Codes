#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using ll = long long;
const int LG = 62;
ll a[LG + 5];
int cnt;

void insert(ll x) {
    DEC(j, LG, 0) {
        if ((x >> j) & 1) {
            if (a[j]) x ^= a[j];
            else {
                a[j] = x;
                DEC(k, j - 1, 0) if (a[k] && ((a[j] >> k) & 1)) a[j] ^= a[k];
                FOR(k, j + 1, LG) if ((a[k] >> j) & 1) a[k] ^= a[j];
                break;
            }
        }
    }
    return;
}

ll kth(ll k) {
    if (k >= (1ll << cnt)) return -1;
    ll ans = 0;
    FOR(i, 0, LG) if (k & (1ll << i)) ans ^= a[i];
    return ans;
}

int main() {
    int T; cin >> T;
    FOR(kase, 1, T) {
        cout << "Case #" << kase << ":\n";
        int n; cin >> n;
        cnt = 0, memset(a, 0, sizeof a);
        FOR(i, 1, n) {
            ll x; cin >> x;
            insert(x);
        }
        FOR(i, 0, LG) if (a[i]) a[cnt++] = a[i];
        int q; cin >> q;
        while (q--) {
            ll k; cin >> k;
            cout << kth(k - (cnt != n)) << endl;
        }
    }
    return 0;
}
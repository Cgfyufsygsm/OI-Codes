#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using ll = long long;
const int LG = 53;
ll a[LG + 5];

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

int main() {
    int n; cin >> n;
    FOR(i, 1, n) {
        ll x; cin >> x;
        insert(x);
    }
    ll ans = 0;
    FOR(i, 0, LG) ans ^= a[i];
    cout << ans << endl;
    return 0;
}
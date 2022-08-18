#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;

const int maxn = 105;
int n, k, a[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        FOR(i, 1, n) cin >> a[i];
        int ans = 0;
        FOR(i, 1, k) ans += (a[i] > k);
        cout << ans << endl;
    }
    return 0;
}
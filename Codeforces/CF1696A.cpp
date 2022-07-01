#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2005;
int n, a[maxn], z;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> z;
        int ans = 0;
        FOR(i, 1, n) cin >> a[i], ans = max(ans, z | a[i]);
        cout << ans << endl;
    }
    return 0;
}
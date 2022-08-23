#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
int n; ll a[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i];
        sort(a + 1, a + n + 1);
        cout << a[n] - a[1] + a[n - 1] - a[2] << endl;
    }
    return 0;
}
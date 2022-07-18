#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
const int maxn = 105;
int n, x, a[maxn << 1];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> x;
        FOR(i, 1, 2 * n) cin >> a[i];
        sort(a + 1, a + 2 * n + 1);
        bool flg = 1;
        FOR(i, 1, n) flg &= (a[i] + x <= a[i + n]);
        puts(flg ? "YES" : "NO");
    }
    return 0;
}
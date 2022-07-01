#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 1e5 + 5;
int n, a[maxn];

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        bool all0 = 1;
        int cnt0 = 0;
        FOR(i, 1, n) cin >> a[i], all0 &= (a[i] == 0), cnt0 += (a[i] == 0);
        if (all0) cout << 0 << '\n';
        else {
            int c1 = 0, c2 = 0;
            FOR(i, 1, n) {
                if (a[i] != 0) break;
                ++c1;
            }
            DEC(i, n, 1) {
                if (a[i] != 0) break;
                ++c2;
            }
            if (c1 + c2 == cnt0) cout << 1 << '\n';
            else cout << 2 << '\n';
        }
    }
    return 0;
}
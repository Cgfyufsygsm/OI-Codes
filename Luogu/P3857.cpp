#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

using ll = long long;
const int LG = 53;
ll a[LG + 5];

int main() {
    int n, m; ll cnt = 0;
    cin >> n >> m;
    char s[LG + 5];
    while (m--) {
        cin >> s;
        ll x = 0;
        FOR(i, 0, n - 1) if (s[i] == 'O') x |= (1ll << i);
        DEC(j, LG, 0) if ((x >> j) & 1) {
            if (!a[j]) a[j] = x;
            x ^= a[j];
        }
    }
    FOR(i, 0, LG) if (a[i]) ++cnt;
    cout << (1ll << cnt) % 2008 << endl;
    return 0;
}
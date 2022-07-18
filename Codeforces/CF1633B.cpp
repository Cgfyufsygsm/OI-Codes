#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
char s[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> (s + 1);
        int n = strlen(s + 1);
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }
        int cnt = 0;
        FOR(i, 1, n) cnt += s[i] - '0';
        if (cnt * 2 != n) cout << min(n - cnt, cnt) << '\n';
        else cout << cnt - 1 << '\n';
    }
    return 0;
}
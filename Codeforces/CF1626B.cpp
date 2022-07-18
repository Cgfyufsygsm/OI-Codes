#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
char s[maxn];
int n;

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> (s + 1);
        n = strlen(s + 1);
        int flg = 0;
        DEC(i, n - 1, 1) {
            if (s[i] - '0' + s[i + 1] - '0' > 9) {
                flg = i;
                break;
            }
        }
        if (flg) {
            FOR(i, 1, flg - 1) cout << s[i];
            cout << s[flg] - '0' + s[flg + 1] - '0';
            FOR(i, flg + 2, n) cout << s[i];
        } else {
            cout << s[1] - '0' + s[2] - '0';
            FOR(i, 3, n) cout << s[i];
        }
        cout << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
char s[maxn], ans[maxn];
int n;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> (s + 1);
        if (s[1] != '9') {
            FOR(i, 1, n) cout << char('9' + '0' - s[i]);
            cout << '\n';
        } else {
            reverse(s + 1, s + n + 1);
            int carry = 0;
            FOR(i, 1, n) {
                if (s[i] - '0' + carry <= 1) {
                    ans[i] = '1' - s[i] + '0' - carry;
                    carry = 0;
                } else {
                    ans[i] = 11 - (s[i] - '0' + carry) + '0';
                    carry = 1;
                }
            }
            reverse(ans + 1, ans + n + 1);
            FOR(i, 1, n) cout << ans[i];
            cout << '\n';
        }
    }
    return 0;
}
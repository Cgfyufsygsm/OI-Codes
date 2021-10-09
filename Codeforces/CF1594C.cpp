#include <iostream>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 3e5 + 5;
char s[maxn], c;
int n;

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> c >> (s + 1);
        bool flag = 1;
        FOR(i, 1, n) flag &= (s[i] == c);
        if (flag) cout << 0 << endl;
        else {
            int ans;
            flag = 0;
            for (ans = 2; ans <= n; ++ans) {
                bool now = 1;
                for (int j = ans; j <= n; j += ans) if (s[j] != c) {now = 0; break;}
                if (now) {flag = 1; break;}
            }
            if (flag) cout << 1 << endl << ans << endl;
            else cout << 2 << endl << n - 1 << ' ' << n << endl;
        }
    }
    return 0;
}
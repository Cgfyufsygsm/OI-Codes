#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const int maxn = 1e6 + 5;
string s[maxn];
int n, m, ok[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n) cin >> s[i];
    int q;
    FOR(j, 2, m) {
        bool flag = 1;
        FOR(i, 2, n) {
            if (s[i][j - 1 - 1] == 'X' && s[i - 1][j - 1] == 'X') {
                flag = 0;
                break;
            }
        }
        ok[j] = flag + ok[j - 1];
    }
    cin >> q;
    while (q--) {
        int c1, c2;
        cin >> c1 >> c2;
        if (c1 == c2) puts("YES");
        else {
            if (ok[c2] - ok[c1] != c2 - c1) puts("NO");
            else puts("YES");
        }
    }
}
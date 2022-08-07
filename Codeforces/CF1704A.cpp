#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 55;
char s[maxn], t[maxn];
int n, m;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        cin >> (s + 1) >> (t + 1);
        bool flg = 1;
        FOR(i, 1, m - 1) flg &= (s[n - i + 1] == t[m - i + 1]);
        if (s[n - m + 1] != t[1]) {
            bool flg2 = 1;
            FOR(i, 1, n - m + 1) flg2 &= (s[i] == s[n - m + 1]);
            if (flg2) flg = 0;
        }
        puts(flg ? "YES" : "NO");
    }
    return 0;
}
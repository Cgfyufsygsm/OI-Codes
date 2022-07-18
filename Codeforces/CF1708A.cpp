#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 105;
int n, a[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        bool flg = 1;
        FOR(i, 1, n) cin >> a[i], flg &= (a[i] % a[1] == 0);
        puts(flg ? "YES" : "NO");
    }
    return 0;
}
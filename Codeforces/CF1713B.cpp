#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;

const int maxn = 2e5 + 5;
int n ,a[maxn];

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i];
        int pos = max_element(a + 1, a + n + 1) - a, flg = 1;
        FOR(i, 1, pos - 1) flg &= (a[i] <= a[i + 1]);
        FOR(i, pos + 1, n) flg &= (a[i - 1] >= a[i]);
        puts(flg ? "YES" : "NO");
    }
    return 0;
}
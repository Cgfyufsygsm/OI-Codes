#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
int n, c, q;
char s[maxn];
ll l[maxn], r[maxn], curlen[maxn];

char solve(ll id) {
    if (id <= n) return s[id];
    int it = lower_bound(curlen, curlen + c + 1, id) - curlen;
    return solve(l[it] + id - curlen[it - 1] - 1);
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> c >> q;
        cin >> (s + 1);
        curlen[0] = n;
        FOR(i, 1, c) {
            cin >> l[i] >> r[i];
            curlen[i] = curlen[i - 1] + r[i] - l[i] + 1;
        }
        while (q--) {
            ll k; cin >> k;
            cout << solve(k) << '\n';
        }
    }
    return 0;
}
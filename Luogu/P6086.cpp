#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 5e6 + 5;
int n, m, f[maxn], p[maxn], d[maxn];
long long ans = 0;

void solve1() {
    FOR(i, 1, n - 1) cin >> f[i], ++d[f[i]];
    for (int i = 1, j = 1; i <= n - 2; ++i, ++j) {
        while (d[j]) ++j;
        p[i] = f[j];
        while (i <= n - 2 && !--d[p[i]] && p[i] < j) p[i + 1] = f[p[i]], ++i;
    }
    FOR(i, 1, n - 2) ans ^= 1ll * i * p[i];
    return;
}

void solve2() {
    FOR(i, 1, n - 2) cin >> p[i], ++d[p[i]];
    p[n - 1] = n;
    for (int i = 1, j = 1; i < n; ++i, ++j) {
        while (d[j]) ++j;
        f[j] = p[i];
        while (i < n && !--d[p[i]] && p[i] < j) f[p[i]] = p[i + 1], ++i;
    }
    FOR(i, 1, n - 1) ans ^= 1ll * i * f[i];
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    if (m == 1) solve1();
    else solve2();
    cout << ans << endl;
    return 0;
}
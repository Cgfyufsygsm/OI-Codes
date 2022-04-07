#include <bits/stdc++.h>
#include <atcoder/all>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

using mint = atcoder::modint1000000007;
const int mod = mint().mod(), maxn = 1e7 + 5;
const mint inv2 = mint(2).inv();
int n, k, d[maxn], tot;
mint f[maxn], ans;

int main() {
    cin >> n >> k;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i) continue;
        d[++tot] = i;
        if (i * i != n) d[++tot] = n / i;
    }
    sort(&d[1], &d[tot] + 1);
    FOR(i, 1, tot) {
        f[i] = atcoder::pow_mod(k, (d[i] + 1) >> 1, mod);
        FOR(j, 1, i - 1) if (!(d[i] % d[j])) f[i] -= f[j];
        ans += (d[i] & 1) ? d[i] * f[i] : d[i] * f[i] * inv2;
    }
    cout << ans.val() << endl;
    return 0;
}
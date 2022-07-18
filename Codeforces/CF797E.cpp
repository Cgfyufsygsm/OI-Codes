#include <bits/stdc++.h>
#include <fastio.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 1e5 + 5, B = 316;
int n, q, a[maxn], f[B + 5][maxn];

int main() {
    is >> n;
    FOR(i, 1, n) is >> a[i];
    FOR(k, 1, B) DEC(i, n, 1) {
        if (i + a[i] + k > n) f[k][i] = 1;
        else f[k][i] = f[k][i + a[i] + k] + 1;
    }
    auto solve = [](int p, const int &k) {
        int cnt = 0;
        while (p <= n) p = p + a[p] + k, ++cnt;
        return cnt;
    };
    is >> q;
    while (q--) {
        int p, k; is >> p >> k;
        if (k <= B) os << f[k][p] << '\n';
        else os << solve(p, k) << '\n';
    }
    return 0;
}
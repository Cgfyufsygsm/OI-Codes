#include <bits/stdc++.h>
#include <atcoder/modint>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using fastIO::is;
using fastIO::os;
using mint = atcoder::modint1000000007;
const int maxn = 105;
int n, a[maxn];
mint f[maxn][maxn][maxn];

int main() {
    is >> n;
    int m = 2 * n - 1;
    FOR(i, 1, m) is >> a[i];
    sort(a + 1, a + m + 1);
    f[n][0][0] = 1;
    DEC(i, n, 2) {
        const int &l = (a[i] != a[i - 1]), &r = (a[m - i + 1] != a[m - i + 2]);
        FOR(j, 0, m) {
            FOR(k, 0, m) {
                if (!f[i][j][k].val()) continue;
                f[i - 1][j + l][k + r] += f[i][j][k];
                FOR(t, 0, j + l - 1) f[i - 1][t][k + r + 1] += f[i][j][k];
                FOR(t, 0, k + r - 1) f[i - 1][j + l + 1][t] += f[i][j][k];
            }
        }
    }
    mint ans = 0;
    FOR(i, 0, m) FOR(j, 0, m) ans += f[1][i][j];
    os << ans.val();
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
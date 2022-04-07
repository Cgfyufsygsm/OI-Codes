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

using mint = atcoder::modint1000000007;
using fastIO::is;
using fastIO::os;

const int maxn = 2e5 + 5, maxm = 4e3 + 5, shift = 2001;
mint f[maxm][maxm], fac[maxm << 1], ifac[maxm << 1];
int n, a[maxn], b[maxn];

int main() {
    is >> n;
    FOR(i, 1, n) {
        is >> a[i] >> b[i];
        ++f[-a[i] + shift][-b[i] + shift];
    }
    FOR(i, -2000, 2000) {
        FOR(j, -2000, 2000) {
            const int &x = i + shift, &y = j + shift;
            f[x][y] += f[x - 1][y] + f[x][y - 1];
        }
    }
    fac[0] = 1;
    FOR(i, 1, 8000) fac[i] = fac[i - 1] * i;
    ifac[8000] = fac[8000].inv();
    DEC(i, 8000 - 1, 0) ifac[i] = (i + 1) * ifac[i + 1];
    auto binom = [](const int &n, const int &m) {return fac[n] * ifac[m] * ifac[n - m];};
    mint ans = 0;
    FOR(i, 1, n) ans += f[a[i] + shift][b[i] + shift] - binom(2 * a[i] + 2 * b[i], 2 * b[i]);
    ans /= 2;
    os << ans.val();
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
#include <bits/stdc++.h>
#include <modint.hpp>
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

using mint = modint1000000007;
const int maxn = 1e5 + 5, N = 1e5, mod = mint().get_mod();

int pri[maxn], vis[maxn], tot, n;
mint mu[maxn], inv[maxn];

void sieve() {
    mu[1] = inv[1] = 1;
    FOR(i, 2, N) {
        if (!vis[i]) pri[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1ll * pri[j] * i <= N; ++j) {
            vis[i * pri[j]] = 1;
            if (!(i % pri[j])) break;
            mu[i * pri[j]] = -mu[i];
        }
        inv[i] = inv[mod % i] * (mod - mod / i);
    }
    return;
}

using fastIO::is;
using fastIO::os;

int main() {
    is >> n;
    mint ans = 1;
    sieve();
    FOR(d, 2, n) ans -= mu[d] * (n / d) * inv[n - (n / d)];
    os << ans.val;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
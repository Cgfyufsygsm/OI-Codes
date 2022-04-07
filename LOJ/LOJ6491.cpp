#include <bits/stdc++.h>
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

using ull = unsigned long long;
const int maxn = 1e7 + 5, N = 1e7;
ull n, m, phi[maxn];
int pri[maxn], tot, vis[maxn];
unordered_map<ull, ull> Phi;

void sieve() {
    phi[1] = 1;
    FOR(i, 2, N) {
        if (!vis[i]) pri[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1ll * i * pri[j] <= N; ++j) {
            vis[i * pri[j]] = 1;
            if (!(i % pri[j])) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            }
            phi[i * pri[j]] = phi[i] * (pri[j] - 1);
        }
    }
    FOR(i, 2, N) phi[i] += phi[i - 1];
    return;
}

ull getSum(ull n) {
    if (n <= N) return phi[n];
    if (Phi[n]) return Phi[n];
    ull ret;
    if (n & 1) ret = (n + 1) / 2 * n;
    else ret = n / 2 * (n + 1);
    for (ull l = 2, r; l <= n; l = r + 1) {
        r = min(n, n / (n / l));
        ret -= (r - l + 1) * getSum(n / l);
    }
    return Phi[n] = ret;
}

ull qPow(ull base, ull exp) {
    ull ret = 1;
    for (; exp; exp >>= 1, base *= base)
        if (exp & 1) ret *= base;
    return ret;
}

int main() {
    sieve();
    cin >> n >> m;
    ull ans = 0;
    for (ull l = 1, r; l <= m; l = r + 1) {
        r = min(m, m / (m / l));
        ans += qPow(m / l, n) * (getSum(r) - getSum(l - 1));
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
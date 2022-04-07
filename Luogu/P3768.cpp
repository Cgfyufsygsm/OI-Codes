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

using ll = long long;
int mod, inv2, inv4, inv6;
ll n;
unordered_map<ll, int> F;
const int maxn = 1e7 + 5, N = 1e7;
int p[maxn], vis[maxn], tot, f[maxn];

void sieve() {
    f[1] = 1;
    FOR(i, 2, N) {
        if (!vis[i]) p[++tot] = i, f[i] = i - 1;
        for (int j = 1; j <= tot && i * p[j] <= N; ++j) {
            vis[i * p[j]] = 1, f[i * p[j]] = f[i] * (p[j] - 1);
            if (!(i % p[j])) {
                f[i * p[j]] = f[i] * p[j];
                break;
            }
        }
    }
    FOR(i, 1, N) f[i] = (1ll * f[i] * i % mod * i % mod + f[i - 1]) % mod;
    return;
}

int qPow(ll base, int exp) {
    int ret = 1;
    for (base %= mod; exp; exp >>= 1, base = base * base % mod)
        if (exp & 1) ret = ret * base % mod;
    return ret;
}

il ll getS2(ll n) {return n % mod * (n + 1) % mod * (2 * n % mod + 1) % mod * inv6 % mod;}

il ll getS2(ll l, ll r) {
    return (getS2(r) - getS2(l - 1) + mod) % mod;
}

il ll getS1(ll n) {
    n %= mod;
    return n * (n + 1) % mod * inv2 % mod;
}

int getSum(ll n) {
    if (n <= N) return f[n];
    if (F[n]) return F[n];
    int ret = getS1(n) * getS1(n) % mod;
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = min(n, n / (n / l));
        ret = (ret - getS2(l, r) * getSum(n / l) % mod + mod) % mod;
    }
    return F[n] = ret;
}

int main() {
    cin >> mod >> n;
    sieve();
    inv2 = qPow(2, mod - 2), inv4 = qPow(4, mod - 2), inv6 = qPow(6, mod - 2);
    int ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = min(n, (n / (n / l)));
        ans = (ans + (getSum(r) - getSum(l - 1) + mod) % mod * getS1(n / l) % mod * getS1(n / l) % mod) % mod;
    }
    cout << ans << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
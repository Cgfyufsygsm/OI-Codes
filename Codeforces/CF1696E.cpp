#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

template<int mod> struct static_modint {
    using mint = static_modint;
    int val;
    inline void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    static_modint(int v = 0) : val(v) {check();}
    inline constexpr int get_mod() {return mod;}

    inline mint &operator=(int v) {return val = v, check(), *this;}
    inline mint &operator+=(mint rhs) {return val = val + rhs.val >= mod ? val + rhs.val - mod : val + rhs.val, *this;}
    inline mint &operator-=(mint rhs) {return val = val - rhs.val < 0 ? val - rhs.val + mod : val - rhs.val, *this;}
    inline mint &operator*=(mint rhs) {return val = 1ll * val * rhs.val % mod, *this;}

    inline friend mint operator+(const mint &lhs, const mint &rhs) {return mint(lhs) += rhs;}
    inline friend mint operator-(const mint &lhs, const mint &rhs) {return mint(lhs) -= rhs;}
    inline friend mint operator*(const mint &lhs, const mint &rhs) {return mint(lhs) *= rhs;}
    inline friend bool operator==(const mint &lhs, const mint &rhs) {return lhs.val == rhs.val;}
    inline friend bool operator!=(const mint &lhs, const mint &rhs) {return lhs.val != rhs.val;}
    inline friend bool operator>(const mint &lhs, const mint &rhs) {return lhs.val > rhs.val;}
    inline friend bool operator<(const mint &lhs, const mint &rhs) {return lhs.val < rhs.val;}
    inline friend bool operator>=(const mint &lhs, const mint &rhs) {return lhs.val >= rhs.val;}
    inline friend bool operator<=(const mint &lhs, const mint &rhs) {return lhs.val <= rhs.val;}

    inline mint &operator++() {
        ++val;
        if (val == mod) val = 0;
        return *this;
    }
    inline mint &operator--() {
        if (val == 0) val = mod;
        --val;
        return *this;
    }
    inline mint operator++(int) {
        mint ret = *this;
        ++*this;
        return ret;
    }
    inline mint operator--(int) {
        mint ret = *this;
        --*this;
        return ret;
    }

    inline mint operator+() const {return *this;}
    inline mint operator-() const {return mint() - *this;}
};

using mint = static_modint<1000000007>;
using namespace std;

const int maxn = 2e5 + 5, N = 4e5;
int a[maxn], n;
mint fac[maxn << 1], ifac[maxn << 1];

mint qPow(mint base, int exp) {
    mint ret = 1;
    for (; exp; exp >>= 1, base *= base)
        if (exp & 1) ret *= base;
    return ret;
}

mint binom(int n, int m) {return n < m ? 0 : fac[n] * ifac[m] * ifac[n - m];}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    fac[0] = 1;
    FOR(i, 1, N) fac[i] = i * fac[i - 1];
    ifac[N] = qPow(fac[N], mint().get_mod() - 2);
    DEC(i, N - 1, 0) ifac[i] = (i + 1) * ifac[i + 1];
    mint ans = 0;
    FOR(i, 0, n) ans += binom(i + a[i], i + 1);
    cout << ans.val << endl;
    return 0;
}
#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {

const int mod = 1e9 + 7;

struct modint {
    typedef int INT;
    static const INT mod = YangTY::mod;
    INT val;
    il void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    modint(INT v = 0) : val(v) {check();}

    il modint &operator=(INT v) {return val = v, *this;}
    il modint &operator+=(modint rhs) {return val = val + rhs.val >= mod ? val + rhs.val - mod : val + rhs.val, *this;}
    il modint &operator-=(modint rhs) {return val = val - rhs.val < 0 ? val - rhs.val + mod : val - rhs.val, *this;}
    il modint &operator*=(modint rhs) {return val = 1ll * val * rhs.val % mod, *this;}

    il friend modint operator+(const modint &lhs, const modint &rhs) {return modint(lhs) += rhs;}
    il friend modint operator-(const modint &lhs, const modint &rhs) {return modint(lhs) -= rhs;}
    il friend modint operator*(const modint &lhs, const modint &rhs) {return modint(lhs) *= rhs;}
    il friend bool operator==(const modint &lhs, const modint &rhs) {return lhs.val == rhs.val;}
    il friend bool operator!=(const modint &lhs, const modint &rhs) {return lhs.val != rhs.val;}
    il friend bool operator>(const modint &lhs, const modint &rhs) {return lhs.val > rhs.val;}
    il friend bool operator<(const modint &lhs, const modint &rhs) {return lhs.val < rhs.val;}
    il friend bool operator>=(const modint &lhs, const modint &rhs) {return lhs.val >= rhs.val;}
    il friend bool operator<=(const modint &lhs, const modint &rhs) {return lhs.val <= rhs.val;}

    il modint &operator++() {
        ++val;
        if (val == mod) val = 0;
        return *this;
    }
    il modint &operator--() {
        if (val == 0) val = mod;
        --val;
        return *this;
    }
    il modint operator++(int) {
        modint ret = *this;
        ++*this;
        return ret;
    }
    il modint operator--(int) {
        modint ret = *this;
        --*this;
        return ret;
    }

    il modint operator+() const {return *this;}
    il modint operator-() const {return modint() - *this;}
};

modint qPow(modint base, modint exp) {
    base.check();
    modint ret = 1;
    for (auto p = exp.val; p; p >>= 1, base *= base)
        if (p & 1) ret *= base;
    return ret;
}

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

const int maxn = 16, maxm = 1005, maxS = 1 << 15;
int n, m, nxt[maxS][4], g[maxn], nxtg[maxn];
char str[maxn];
modint f[2][maxS], ans[maxn];

void initNxt() {
    FOR(i, 1, n) {
        if (str[i] == 'A') str[i] = 0;
        else if (str[i] == 'T') str[i] = 1;
        else if (str[i] == 'G') str[i] = 2;
        else if (str[i] == 'C') str[i] = 3;
    }
    FOR(S0, 0, (1 << n) - 1) {
        for (int j = 1, i = S0; j <= n; ++j, i >>= 1) g[j] = (i & 1) + g[j - 1];
        FOR(c, 0, 3) {
            int newS = 0;
            FOR(i, 1, n) {
                if (c == str[i]) nxtg[i] = g[i - 1] + 1;
                else nxtg[i] = max(nxtg[i - 1], g[i]);
                newS += (nxtg[i] - nxtg[i - 1]) * (1 << (i - 1));
            }
            nxt[S0][c] = newS;
        }
    }
    return;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> str + 1 >> m;
        n = strlen(str + 1);
        initNxt();
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        FOR(i, 0, m - 1) {
            memset(f[(i & 1) ^ 1], 0, sizeof f[(i & 1) ^ 1]);
            FOR(c, 0, 3) FOR(j, 0, (1 << n) - 1) f[(i & 1) ^ 1][nxt[j][c]] += f[i & 1][j];
        }
        memset(ans, 0, sizeof ans);
        FOR(j, 0, (1 << n) - 1) ans[__builtin_popcount(j)] += f[(m & 1)][j];
        FOR(i, 0, n) cout << ans[i].val << '\n';
    }
    return 0;
}
}// namespace YangTY

int main() {
    YangTY::main();
    return 0;
}

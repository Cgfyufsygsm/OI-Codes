#include <bits/stdc++.h>
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {

const int mod = 998244353;

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

using ll = long long;
using ull = unsigned long long;

namespace polynomial {
const int maxn = 1 << 19 | 500;
using Poly = vector<int>;
const Poly one(1, 1);

ll qPow(ll a, ll b = mod - 2) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ret = a * ret % mod;
    return ret;
}

int tr[maxn << 1], revLim, lim;
void getTr(int n) {
    if (revLim == n) return;
    revLim = n;
    FOR(i, 0, n - 1)
        tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
}

Poly operator+(const Poly &A, const Poly &B) {
    Poly C = A; C.resize(max(A.size(), B.size()));
    VEC(i, B) C[i] = (C[i] + B[i]) % mod;
    return C;
}
Poly operator-(const Poly &A, const Poly &B) {
    Poly C = A; C.resize(max(A.size(), B.size()));
    VEC(i, B) C[i] = (C[i] + mod - B[i]) % mod;
    return C;
}
Poly operator*(const int c, const Poly &A) {
    Poly C = A;
    VEC(i, A) C[i] = 1ll * c * C[i] % mod;
    return C;
}
Poly operator-(const Poly &A) {
    Poly ret; ret.resize(A.size());
    VEC(i, A) ret[i] = mod - A[i];
    return ret;
}

const int G = 3, invG = qPow(G);

void DFT(int *g, bool op, int n) {
    getTr(n);
    static ull f[maxn << 1], w[maxn << 1];
    w[0] = 1;
    FOR(i, 0, n - 1) f[i] = (((ll)mod << 5ll) + g[tr[i]]) % mod;
    for (int l = 1; l < n; l <<= 1) {
        ull tG = qPow(op ? G : invG, (mod - 1) / (l << 1));
        FOR(i, 1, l - 1) w[i] = w[i - 1] * tG % mod;
        for (int k = 0; k < n; k += (l << 1))
            for (int p = 0; p < l; ++p) {
                int tt = w[p] * f[k | l | p] % mod;
                f[k | l | p] = f[k | p] + mod - tt;
                f[k | p] += tt;
            }
        if (l == (1 << 10))
            FOR(i, 0, n - 1) f[i] %= mod;
    }
    if (!op) {
        ull invn = qPow(n);
        FOR(i, 0, n - 1) g[i] = f[i] % mod * invn % mod;
    } else FOR(i, 0, n - 1) g[i] = f[i] % mod;
}

void mul(int *f, int *g, int n) {
    FOR(i, 0, n - 1) f[i] = 1ll * f[i] * g[i] % mod;
    return;
}

Poly operator*(const Poly &A, const Poly &B) {
    static int a[maxn << 1], b[maxn << 1];
    cpy(a, &A[0], A.size());
    cpy(b, &B[0], B.size());
    Poly C; C.resize(min(lim, (int)(A.size() + B.size() - 1)));
    int n = 1; for (n = 1; n < (int)(A.size() + B.size() - 1); n <<= 1);
    DFT(a, 1, n), DFT(b, 1, n);
    mul(a, b, n), DFT(a, 0, n);
    cpy(&C[0], a, C.size());
    clr(a, n), clr(b, n);
    return C;
}

void polyInv(const Poly &A, Poly &B, int n) {
    if (!n) return;
    if (n == 1) B.push_back(qPow(A[0]));
    else if (n & 1) {
        polyInv(A, B, --n);
        int sav = 0;
        FOR(i, 0, n - 1) sav = (sav + 1ll * B[i] * A[n - i]) % mod;
        B.push_back(1ll * sav * qPow(mod - A[0]) % mod);
    } else {
        polyInv(A, B, n >> 1);
        Poly sA; sA.resize(n);
        cpy(&sA[0], &A[0], n);
        B = 2 * B - B * B * sA;
        B.resize(n);
    }
    return;
}
Poly polyInv(const Poly &A) {
    Poly C; polyInv(A, C, A.size());
    return C;
}

int inv[maxn];
void initInv() {
    inv[1] = 1;
    FOR(i, 2, lim) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    return;
}

Poly deri(const Poly &A) {
    Poly C = A;
    for (int i = 1; i < (int)C.size(); ++i) C[i - 1] = 1ll * C[i] * i % mod;
    if (!C.empty()) C.pop_back();
    return C;
}

Poly ints(const Poly &A) {
    Poly C = A;
    for (int i = (int)C.size() - 1; i > 0; --i)
        C[i] = 1ll * C[i - 1] * inv[i] % mod;
    if (!C.empty()) C[0] = 0;
    else C.push_back(0);
    return C;
}

Poly polyLn(const Poly &A) {
    return ints(deri(A) * polyInv(A));
}

void polyExp(const Poly &A, Poly &B, int n) {
    if (!n) return;
    if (n == 1) B.push_back(1);
    else if (n & 1) {
        polyExp(A, B, n - 1); n -= 2;
        int sav = 0;
        FOR(i, 0, n) sav = (sav + 1ll * (i + 1) * A[i + 1] % mod * B[n - i]) % mod;
        B.push_back(1ll * sav * inv[n + 1] % mod);
    } else {
        polyExp(A, B, n / 2);
        Poly lnB = B;
        lnB.resize(n); lnB = polyLn(lnB);
        VEC(i, lnB) lnB[i] = (mod + A[i] - lnB[i]) % mod;
        ++lnB[0];
        B = B * lnB;
        B.resize(n);
    }
    return;
}

Poly polyExp(const Poly &f) {
    Poly ret;
    polyExp(f, ret, f.size());
    return ret;
}
} // namespace polynomial

using namespace polynomial;

namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
il void print(modint x, char c = '\n') {print(x.val, c);}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

modint fac[maxn], ifac[maxn];
int n, m;

modint binom(int n, int m) {
    return n < m ? 0 : fac[n] * ifac[m] * ifac[n - m];
}

int main() {
    read(n, m);
    lim = max(n, m) << 1;
    fac[0] = 1;
    FOR(i, 1, lim) fac[i] = fac[i - 1] * i;
    ifac[lim] = qPow(fac[lim], mod - 2);
    DEC(i, lim - 1, 0) ifac[i] = (i + 1) * ifac[i + 1];
    initInv();
    print(qPow(m, n)); // subtask 1
    modint ans2 = 1;
    DEC(i, m, m - n + 1) ans2 *= i;
    print(ans2); // subtask 2
    modint ans3 = 0;
    FOR(i, 0, m) ans3 += (i & 1 ? -1 : 1) * binom(m, i) * qPow(m - i, n);
    print(ans3); // subtask 3

    Poly f, g;
    f.resize(n + 1), g.resize(n + 1);
    FOR(i, 0, n) f[i] = ((i & 1) ? -ifac[i] : ifac[i]).val, g[i] = (qPow(i, n) * ifac[i]).val;
    f = f * g;
    modint ans4;
    FOR(i, 1, min(n, m)) ans4 += f[i];
    print(ans4); // subtask 4
    print(n <= m ? 1 : 0); // subtask 5
    print(m > n ? 0 : f[m]); // subtask 6

    print(binom(n + m - 1, m - 1)); // subtask 7
    print(binom(m, n)); // subtask 8
    print(binom(n - 1, m - 1)); // subtask 9

    Poly h; h.resize(lim);
    FOR(k, 1, m) for (int i = 1; i * k < lim; ++i) h[i * k] = (h[i * k] + inv[i]) % mod;
    h = (polyExp(h));
    print(h[n]); // subtask 10
    print(n <= m ? 1 : 0); // subtask 11
    print(n >= m ? h[n - m] : 0); // subtask 12
    return output(), 0;
}
}// namespace YangTY

int main() {
    YangTY::main();
    return 0;
}

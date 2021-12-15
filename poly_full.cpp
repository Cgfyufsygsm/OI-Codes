#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))
#define NTT

using namespace std;

namespace YangTY {

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

using ll = long long;
using ull = unsigned long long;

#ifdef NTT
const int mod = 998244353;
#else
int mod;
#endif

namespace polynomial {
const int maxn = 1 << 17 | 500, imgunit = 86583718;
using Poly = vector<int>;
const Poly one(1, 1);

ll qPow(ll a, ll b = mod - 2) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ret = a * ret % mod;
    return ret;
}

namespace quad_residue {
using polynomial::qPow;

struct Cmplx {
    int x, y;
};
int w;

il Cmplx operator*(const Cmplx &a, const Cmplx &b) {
    Cmplx ans = {0, 0};
    ans.x = ((1ll * a.x * b.x % mod + 1ll * a.y * b.y % mod * w % mod) + mod) % mod;
    ans.y = ((1ll * a.x * b.y % mod + 1ll * a.y * b.x % mod) + mod) % mod;
    return ans;
}

int qPow(Cmplx a, int b) {
    Cmplx ans = {1, 0};
    for (; b; b >>= 1, a = a * a)
        if (b & 1) ans = ans * a;
    return ans.x % mod;
}

int cipolla(int n) {
    n %= mod;
    if (mod == 2) return n;
    if (qPow(n, (mod - 1) / 2) == mod - 1) return -1;
    int a;
    while (1) {
        a = rand() % mod;
        w = ((1ll * a * a % mod - n) % mod + mod) % mod;
        if (qPow(w, (mod - 1) / 2) == mod - 1) break;
    }
    Cmplx x = {a, 1};
    int res = qPow(x, (mod + 1) / 2);
    return min(res, mod - res);
}
} // namespace quad_residue

using quad_residue::cipolla;

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

#ifdef NTT
#undef NTT
namespace NTT {
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
} // namespace NTT
using NTT::operator*;
#else
namespace MTT {

using db = long double;

using std::sin;
using std::cos;
using std::acos;
using std::floor;
const db PI = acos(-1.0);
const int DIV = 32768;

namespace complex {
struct Cmplx {
    db x, y;
    Cmplx(db xx = 0, db yy = 0) : x(xx), y(yy) {}
};
il Cmplx operator+(const Cmplx &a, const Cmplx &b) {return Cmplx(a.x + b.x, a.y + b.y);}
il Cmplx operator-(const Cmplx &a, const Cmplx &b) {return Cmplx(a.x - b.x, a.y - b.y);}
il Cmplx operator*(const Cmplx &a, const Cmplx &b) {return Cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}
} // namespace complex 

using namespace complex;

#define clr2(f, n) memset(f, 0, (sizeof(Cmplx)) * n)

void DFT(Cmplx *g, int type, int lim) {
    static Cmplx f[maxn << 1];
    getTr(lim);
    FOR(i, 0, lim - 1) f[i] = g[tr[i]];
    for (int p = 2; p <= lim; p <<= 1) {
        int len = p >> 1;
        Cmplx Wp(cos(PI / len), type * sin(PI / len));
        for (int k = 0; k < lim; k += p) {
            Cmplx w(1, 0);
            for (int l = k; l < k + len; ++l, w = w * Wp) {
                Cmplx tmp = w * f[len + l];
                f[len + l] = f[l] - tmp;
                f[l] = f[l] + tmp;
            }
        }
    }
    FOR(i, 0, lim - 1)
        if (type == -1) g[i] = Cmplx(f[i].x / lim, f[i].y / lim);
        else g[i] = f[i];
    return;
}

Poly operator*(Poly A, Poly B) {
    static Cmplx p1[maxn << 1], p2[maxn << 1], q[maxn << 1], t1[maxn << 1], t2[maxn << 1];
    VEC(i, A) p1[i] = Cmplx(A[i] / DIV, A[i] % DIV), p2[i] = Cmplx(A[i] / DIV, -p1[i].y);
    VEC(i, B) q[i] = Cmplx(B[i] / DIV, B[i] % DIV);
    Poly C; C.resize(min(lim, (int)A.size() + (int)B.size() - 1));
    int n; for (n = 1; n < (int)(A.size() + B.size() - 1); n <<= 1);

    DFT(p1, 1, n), DFT(p2, 1, n), DFT(q, 1, n);
    FOR(i, 0, n - 1) t1[i] = p1[i] * q[i], t2[i] = p2[i] * q[i];
    DFT(t1, -1, n), DFT(t2, -1, n);

    VEC(i, C) {
        ll a1b1, a1b2, a2b1, a2b2;
        a1b1 = (ll)floor((t1[i].x + t2[i].x) / 2.0 + 0.49) % mod;
        a1b2 = (ll)floor((t1[i].y + t2[i].y) / 2.0 + 0.49) % mod;
        a2b1 = ((ll)floor(t1[i].y + 0.49) - a1b2) % mod;
        a2b2 = ((ll)floor(t2[i].x + 0.49) - a1b1) % mod;
        C[i] = ((((a1b1 << 15) + (a1b2 + a2b1)) << 15) + a2b2) % mod;
        C[i] = (C[i] + mod) % mod;
    }

    clr2(p1, n), clr2(p2, n), clr2(q, n), clr2(t1, n), clr2(t2, n);
    return C;
}
} // namespace MTT

using MTT::operator*;
#endif

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

Poly polyPow(const Poly &f, int k) {
    return polyExp(k * polyLn(f));
}

void polySqrt(const Poly &A, Poly &B, int m) {
    if (m == 1) {
        B.push_back(cipolla(A[0]));
        return;
    }
    polySqrt(A, B, (m + 1) >> 1);
    B.resize(m);
    Poly invB = polyInv(2 * B), sA(A.begin(), A.begin() + m);
    B = qPow(2) * B + invB * sA;
    return;
}

Poly polySqrt(const Poly &A) {
    Poly C; polySqrt(A, C, A.size());
    return C;
}

il void reverse(Poly &A) {
    reverse(A.begin(), A.end());
}

void polyDiv(const Poly &A, const Poly &B, Poly &Q, Poly &R) {
    Poly rA = A, rB = B;
    reverse(rA), reverse(rB);
    int n = A.size(), m = B.size();
    rA.resize(n - m + 1), rB.resize(n - m + 1);
    Q = rA * polyInv(rB), Q.resize(n - m + 1), reverse(Q);
    R = A - B * Q, R.resize(m - 1);
    return;
}

Poly polySin(const Poly &A) {
    Poly tmp = polyExp(imgunit * A);
    return qPow(1ll * 2 * imgunit % mod) * (tmp - polyInv(tmp));
}

Poly polyCos(const Poly &A) {
    Poly tmp = polyExp(imgunit * A);
    return qPow(2) * (tmp + polyInv(tmp));
}

Poly polyAsin(const Poly &A) {
    Poly one; one.push_back(1);
    return ints(deri(A) * polyInv(polySqrt(one - A * A)));
}

Poly polyAtan(const Poly &A) {
    Poly one; one.push_back(1);
    return ints(deri(A) * polyInv(one + A * A));
}

namespace multi_eval_and_interpolation {

#define L (k << 1)
#define R (L | 1)
#define M ((l + r) >> 1)
Poly g[maxn << 2], Q;

void initG(int k, int l, int r, int *a) {
    if (l == r) {
        g[k].push_back(a[l] ? mod - a[l] : 0);
        g[k].push_back(1);
        return;
    }
    initG(L, l, M, a);
    initG(R, M + 1, r, a);
    g[k] = g[L] * g[R];
    return;
}

void evaluate(int k, int l, int r, Poly A, int *a, int *ans) {
    if (r - l + 1 < 100) {
        FOR(i, l, r) {
            int s = 0;
            DEC(j, A.size() - 1, 0)
                s = (1ll * s * a[i] % mod + A[j]) % mod;
            ans[i] = s;
        }
        return;
    }
    Poly B;
    polyDiv(A, g[L], Q, B);
    evaluate(L, l, M, B, a, ans);
    polyDiv(A, g[R], Q, B);
    evaluate(R, M + 1, r, B, a, ans);
    return;
}

void evaluate(Poly f, int m, int *a, int *ans) {
    initG(1, 1, m, a);
    evaluate(1, 1, m, f, a, ans);
    return;
}

Poly delta[maxn << 2], ddelta;
int dval[maxn];

void initDelta(int k, int l, int r, int *x) {
    if (l == r) {
        delta[k].push_back(x[l] ? mod - x[l] : 0);
        delta[k].push_back(1);
        return;
    }
    initDelta(L, l, M, x);
    initDelta(R, M + 1, r, x);
    delta[k] = delta[L] * delta[R];
    return;
}

Poly interpolation(int k, int l, int r, int *x, int *y) {
    if (l == r)
        return Poly(1, 1ll * y[l] * qPow(dval[l]) % mod);
    return interpolation(L, l, M, x, y) * delta[R] + interpolation(R, M + 1, r, x, y) * delta[L];
}

Poly interpolation(int n, int *x, int *y) {
    initDelta(1, 1, n, x);
    ddelta = deri(delta[1]);
    evaluate(ddelta, n, x, dval);
    return interpolation(1, 1, n, x, y);
}
#undef L
#undef R
#undef M
} // namespace multi_eval_and_interpolation

using multi_eval_and_interpolation::evaluate;
using multi_eval_and_interpolation::interpolation;
} // namespace polynomial

using namespace polynomial;
// warning: don't forget to set lim

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
    while (!isspace(c)) s[p++] = c, c = getchar();
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
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

int main() {
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define ll long long
#define ull unsigned long long
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))
#define MOD 998244353

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

namespace poly {
#define int int
    const int G = 3, mod = MOD, maxn = 1 << 17 | 500, imgunit = 86583718;
    typedef std::vector<int> Poly;
    ll qPow(ll a, ll b = mod - 2) {
        ll ret = 1;
        for (; b; b >>= 1, a = a * a % mod)
            if (b & 1) ret = a * ret % mod;
        return ret;
    }
    const int invG = qPow(G);

    int tr[maxn << 1], revLim, lim;

    void getTr(int n) {
        if (revLim == n) return;
        revLim = n;
        FOR(i, 0, n - 1)
            tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }

    void NTT(int *g, bool op, int n) {
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

    Poly operator*(const Poly &A, const Poly &B) {
        static int a[maxn << 1], b[maxn << 1];
        cpy(a, &A[0], A.size());
        cpy(b, &B[0], B.size());
        Poly C; C.resize(min(lim, (int)(A.size() + B.size() - 1)));
        int n = 1; for (n = 1; n < (int)(A.size() + B.size() - 1); n <<= 1);
        NTT(a, 1, n), NTT(b, 1, n);
        mul(a, b, n), NTT(a, 0, n);
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

    il void reverse(Poly &A) {
        std::reverse(A.begin(), A.end());
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
    #undef L
    #undef R
    #undef M
#undef int
} using namespace poly;

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
        while (!isdigit(c) && !isalpha(c)) c = getchar();
        while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
        return;
    }
    char obuf[maxc], *__pO = obuf;
    il void putchar(char c) {*__pO++ = c;}
    template<typename T> void print(T x) {
        if (x < 0) putchar('-'), print(-x);
        else {
            if (x > 9) print(x / 10);
            putchar(x % 10 + '0');
        }
        return;
    }
    void print(Poly A) {
        VEC(i, A) print(A[i]), putchar(' ');
        putchar('\n');
        return;
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} using namespace fastIO;

int n, m;
Poly f;
int a[maxn], ans[maxn];

int main() {
    read(n), read(m);
    f.resize(lim = ++n);
    FOR(i, 0, n - 1) read(f[i]);
    FOR(i, 1, m) read(a[i]);
    evaluate(f, m, a, ans);
    FOR(i, 1, m) print(ans[i]), putchar('\n');
    return output(), 0;
}
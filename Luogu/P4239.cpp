#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <cmath>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define ll long long
#define ull unsigned long long
#define db long double
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

namespace poly {
    const int maxn = (1 << 18) + 500;
    int mod;

    ll qPow(ll a, ll b = mod - 2) {
        ll ret = 1;
        for (; b; b >>= 1, a = a * a % mod)
            if (b & 1) ret = a * ret % mod;
        return ret;
    }

    typedef std::vector<int> Poly;
    int tr[maxn << 1], revLim, lim;

    void getTr(int n) {
        if (revLim == n) return;
        revLim = n;
        FOR(i, 0, n - 1)
            tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }

    namespace complex {
        struct cmplx {
            db x, y;
            cmplx(db xx = 0, db yy = 0) : x(xx), y(yy) {}
        };
        il cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
        il cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
        il cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}
    } using namespace complex;

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

    namespace MTT {
        using std::sin;
        using std::cos;
        using std::acos;
        using std::floor;
        const db PI = acos(-1.0);
        const int DIV = 32768;

        #define clr2(f, n) memset(f, 0, (sizeof(cmplx)) * n)

        void DFT(cmplx *g, int type, int lim) {
            static cmplx f[maxn << 1];
            getTr(lim);
            FOR(i, 0, lim - 1) f[i] = g[tr[i]];
            for (int p = 2; p <= lim; p <<= 1) {
                int len = p >> 1;
                cmplx Wp(std::cos(PI / len), type * std::sin(PI / len));
                for (int k = 0; k < lim; k += p) {
                    cmplx w(1, 0);
                    for (int l = k; l < k + len; ++l, w = w * Wp) {
                        cmplx tmp = w * f[len + l];
                        f[len + l] = f[l] - tmp;
                        f[l] = f[l] + tmp;
                    }
                }
            }
            FOR(i, 0, lim - 1)
                if (type == -1) g[i] = cmplx(f[i].x / lim, f[i].y / lim);
                else g[i] = f[i];
            return;
        }

        Poly operator*(const Poly &A, const Poly &B) {
            static cmplx p1[maxn << 1], p2[maxn << 1], q[maxn << 1], t1[maxn << 1], t2[maxn << 1];
            VEC(i, A) p1[i] = cmplx(A[i] / DIV, A[i] % DIV), p2[i] = cmplx(A[i] / DIV, -p1[i].y);
            VEC(i, B) q[i] = cmplx(B[i] / DIV, B[i] % DIV);
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
    } using namespace MTT;

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

Poly f;

int main() {
    int n;
    read(n), mod = 1e9 + 7;
    f.resize(lim = n);
    FOR(i, 0, n - 1) read(f[i]);
    print(polyInv(f));
    return output(), 0;
}
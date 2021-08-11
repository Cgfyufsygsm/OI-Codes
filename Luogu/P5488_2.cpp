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
#define MOD 1004535809

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

namespace poly {
#define int int
    const int G = 3, mod = MOD, maxn = 1 << 17 | 500;
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

    int inv[maxn];
    void initInv() {
        inv[1] = 1;
        FOR(i, 2, lim) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
        return;
    }
#undef int
} using namespace poly;

namespace fastIO {
    const int maxc = 1 << 23;
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

int n, k, t;
char s[3000];
Poly f, g;

int main() {
    scanf("%d %s %d", &n, s + 1, &t);
    for (int i = 1; s[i]; ++i)
        k = (10ll * k + s[i] - '0') % mod;
    lim = n, initInv();
    f.resize(n), g.resize(n);
    FOR(i, 0, n - 1) scanf("%d", &f[i]);
    if (!t) {
        g[0] = 1;
        FOR(i, 1, n - 1) g[i] = 1ll * g[i - 1] * (k + i - 1) % mod * inv[i] % mod;
    } else {
        g[0] = 1;
        FOR(i, 1, n - 1) g[i] = 1ll * (mod - 1) * (k - i + 1) % mod * inv[i] % mod * g[i - 1] % mod;
    }
    print(f * g);
    return output(), 0;
}
#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define il inline
#define clr(f, n) memset(f, 0, (sizeof(modint)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(modint)) * (n))
#define MOD 998244353

struct modint {
    typedef int INT;
    static const INT mod = MOD;
    INT val;
    il void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    modint(INT v = 0) : val(v) {check();}

    il modint &operator=(INT v) {return val = v, *this;}
    il modint &operator+=(modint rhs) {return val = val + rhs.val > mod ? val + rhs.val - mod : val + rhs.val, *this;}
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
    
    friend modint qPow(modint base, modint exp) {
    	base.check();
    	modint ret = 1;
    	for (INT p = exp.val; p; p >>= 1, base *= base)
    		if (p & 1) ret *= base;
    	return ret;
	}
};

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
    void print(modint x) {
        print(x.val);
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} using namespace fastIO;

namespace poly {
    const modint mod = MOD, G = 3, invG = qPow(G, mod - 2);
    const int maxn = ((1 << 18) + 500);

    int rev[maxn << 1], revLim;

    void getRev(int lim) {
        if (lim == revLim) return;
        revLim = lim;
        FOR(i, 0, revLim - 1)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
        return;
    }
    
    void NTT(modint *g, int n, int type) {
        getRev(n);
        static modint f[maxn << 1], w[maxn << 1];
        w[0] = 1;
        FOR(i, 0, n - 1) f[i] = g[rev[i]];

        for (int l = 1; l < n; l <<= 1) {
            modint tmp = qPow(type ? G : invG, (MOD - 1) / (l << 1));
            FOR(i, 1, l - 1) w[i] = w[i - 1] * tmp;
            for (int i = 0; i < n; i += (l << 1)) {
                for (int j = 0; j < l; ++j) {
                    modint tt = w[j] * f[i + j + l];
                    f[i + j + l] = f[i + j] - tt;
                    f[i + j] += tt;
                }
            }
        }
        if (!type) {
            modint invn = qPow(n, mod - 2);
            FOR(i, 0, n - 1) g[i] = f[i] * invn;
        } else FOR(i, 0, n - 1) g[i] = f[i];
        return;
    }

    void times(modint *f, modint *g, int len, int lim) {
        static modint sav[maxn << 1];
        int n = 1;
        while (n < (len << 1)) n <<= 1;
        clr(sav, n), cpy(sav, g, n);
        NTT(f, n, 1), NTT(sav, n, 1);
        FOR(i, 0, n - 1) f[i] *= sav[i];
        NTT(f, n, 0);
        clr(f + lim, n - lim), clr(sav, n);
    }

    void polyInv(modint *f, int m) {
        int n;
        for (n = 1; n < m; n <<= 1);
        static modint w[maxn << 1], r[maxn << 1], sav[maxn << 1];
        w[0] = qPow(f[0], mod - 2);
        for (int len = 2; len <= n; len <<= 1) {
            FOR(i, 0, (len >> 1) - 1)
                r[i] = 2 * w[i];
            cpy(sav, f, len);
            NTT(w, len << 1, 1);
            FOR(i, 0, (len << 1) - 1) w[i] *= w[i];
            NTT(sav, len << 1, 1);
            FOR(i, 0, (len << 1) - 1) w[i] *= sav[i];
            NTT(w, len << 1, 0);
            clr(w + len, len);
            FOR(i, 0, len - 1)
                w[i] = r[i] - w[i];
        }
        cpy(f, w, m);
        clr(sav, n << 1), clr(w, n << 1), clr(r, n << 1);
    }

    modint inv[maxn];
    void initInv(int lim) {
        inv[1] = 1;
        FOR(i, 2, lim)
            inv[i] = 1ll * inv[MOD % i] * (mod - MOD / i);
        return;
    }

    void derivate(modint *f, int m) {
        FOR(i, 1, m - 1)
            f[i - 1] = i * f[i];
        f[m - 1] = 0;
    }

    void intergrate(modint *f, int m) {
        DEC(i, m, 1)
            f[i] = f[i - 1] * inv[i];
        f[0] = 0;
        return;
    }

    void polyLn(modint *f, int m) {
        static modint invf[maxn << 1];
        int lim = 1;
        while (lim < m << 1) lim <<= 1;
        initInv(lim);
        cpy(invf, f, m), polyInv(invf, m);
        derivate(f, m);
        NTT(f, lim, 1), NTT(invf, lim, 1);
        FOR(i, 0, lim - 1) f[i] *= invf[i];
        NTT(f, lim, 0), intergrate(f, m);
        clr(invf, lim);
        clr(f + m, lim - m);
        return;
    }

    void polyExp(modint *f, int m) {
        int n;
        for (n = 1; n < m; n <<= 1);
        static modint s[maxn << 1], s2[maxn << 1];
        s2[0] = 1;
        for (int len = 2; len <= n; len <<= 1) {
            cpy(s, s2, len >> 1);
            polyLn(s, len);
            FOR(i, 0, len - 1) s[i] = f[i] - s[i];
            ++s[0];
            times(s2, s, len, len);
        }
        cpy(f, s2, m), clr(s, n), clr(s2, n);
        return;
    }
} using namespace poly;

template<typename T> il T min(T &a, T &b) {return a < b ? a : b;}
template<typename T> il T max(T &a, T &b) {return a > b ? a : b;}

int n;
modint f[maxn << 1], k;

int main() {
    read(n), read(k);
    FOR(i, 0, n - 1) read(f[i]);
    polyLn(f, n);
    FOR(i, 0, n - 1) f[i] *= k;
    polyExp(f, n);
    FOR(i, 0, n - 1) print(f[i]), putchar(' ');
    return output(), 0;
}
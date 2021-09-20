#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int mod = 998244353;

struct modint {
    typedef int INT;
    static const INT mod = ::mod;
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
}

using namespace fastIO;

const int maxn = 3600 + 5;
int n, m, k;

modint fac[maxn], invfac[maxn];
int visx[maxn], visy[maxn], nn, mm;
modint f[maxn][maxn], g[maxn][maxn];

modint binom(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    return fac[n] * invfac[n - m] * invfac[m];
}

int main() {
    fac[0] = 1;
    FOR(i, 1, 3600) fac[i] = i * fac[i - 1];
    invfac[3600] = qPow(fac[3600], mod - 2);
    DEC(i, 3600 - 1, 0) invfac[i] = (i + 1) * invfac[i + 1];

    read(n), read(m), read(k);
    FOR(i, 1, k) {
        int x1, y1, x2, y2;
        read(x1), read(y1), read(x2), read(y2);
        visx[x1] = visx[x2] = 1;
        visy[y1] = visy[y2] = 1;
    }

    FOR(i, 1, n) nn += (!visx[i]);
    FOR(i, 1, m) mm += (!visy[i]);

    f[0][0] = 1;
    FOR(i, 1, n)
        FOR(j, 0, nn / 2)
            f[i][j] = f[i - 1][j] + ((j && i > 1 && !visx[i] && !visx[i - 1]) ? f[i - 2][j - 1] : 0);
    g[0][0] = 1;
    FOR(i, 1, m)
        FOR(j, 0, mm / 2)
            g[i][j] = g[i - 1][j] + ((j && i > 1 && !visy[i] && !visy[i - 1]) ? g[i - 2][j - 1] : 0);

    modint ans = 0;
    FOR(x, 0, nn / 2) {
        FOR(y, 0, mm / 2) {
            ans += f[n][x] * g[m][y] * fac[x] * fac[y] * binom(mm - 2 * y, x) * binom(nn - 2 * x, y);
        }
    }
    print(ans);
    return output(), 0;
}

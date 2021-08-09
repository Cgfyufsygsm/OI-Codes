#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define cpy(x, y) memcpy(y, x, sizeof x)
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

const int maxn = 1 << 19;

int n;
modint A[maxn], B[maxn], a[maxn], b[maxn];

void OR(modint *f, modint x = 1) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; ++j)
                f[i + j + k] += f[i + j] * x;
    return;
}

void AND(modint *f, modint x = 1) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; ++j)
                f[i + j] += f[i + j + k] * x;
    return;
}

void XOR(modint *f, modint x = 1) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            for (int j = 0; j < k; ++j) {
                f[i + j] += f[i + j + k];
                f[i + j + k] = f[i + j] - f[i + j + k] - f[i + j + k];
                f[i + j] *= x, f[i + j + k] *= x;
            }
    return;
}

void mul(modint *f, modint *g) {
    FOR(i, 0, n) f[i] *= g[i];
    return;
}

int main() {
    read(n);
    n = 1 << n;
    FOR(i, 0, n - 1) read(A[i]);
    FOR(i, 0, n - 1) read(B[i]);
    
    cpy(A, a), cpy(B, b), OR(a, 1), OR(b, 1), mul(a, b), OR(a, MOD - 1);
    FOR(i, 0, n - 1) print(a[i]), putchar(' '); putchar('\n');

    cpy(A, a), cpy(B, b), AND(a, 1), AND(b, 1), mul(a, b), AND(a, MOD - 1);
    FOR(i, 0, n - 1) print(a[i]), putchar(' '); putchar('\n');

    cpy(A, a), cpy(B, b), XOR(a, 1), XOR(b, 1), mul(a, b), XOR(a, (MOD + 1) / 2);
    FOR(i, 0, n - 1) print(a[i]), putchar(' '); putchar('\n');

    return output(), 0;
}
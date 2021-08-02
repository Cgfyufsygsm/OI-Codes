#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

const int maxn = 3e6 + 5, mod = 1e9 + 7;
int f[maxn][3], n, q;

int fac[maxn], invfac[maxn];

int qPow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1) ret = 1ll * ret * a % mod;
    return ret;
}

int binom(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return 1ll * fac[n] * invfac[n - m] % mod * invfac[m] % mod;
}

void init() {
    int inv3 = qPow(3, mod - 2, mod);
    fac[0] = 1;
    FOR(i, 1, 3 * n) fac[i] = 1ll * fac[i - 1] * i % mod;
    invfac[3 * n] = qPow(fac[3 * n], mod - 2, mod);
    DEC(i, 3 * n - 1, 0) invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;

    f[0][0] = f[0][1] = f[0][2] = n;
    FOR(x, 1, 3 * n) {
        f[x][0] = (((1ll * binom(3 * n, x + 1) - 2ll * f[x - 1][0] - f[x - 1][1] + 3ll * mod) % mod) * inv3) % mod;
        f[x][1] = (f[x][0] + f[x - 1][0]) % mod;
        f[x][2] = (f[x][1] + f[x - 1][1]) % mod;
    }
    return;
}

int main() {
    read(n), read(q);
    init();
    while (q--) {
        int x; read(x);
        if (x == 3 * n) print(1), putchar('\n');
        else print((f[x][0] + binom(3 * n, x)) % mod), putchar('\n');
    }
    return output(), 0;
}
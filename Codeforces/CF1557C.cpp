#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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
}

using namespace fastIO;

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;

int t, n, k;

int qPow(int base, int p) {
    int ret = 1;
    for (; p; p >>= 1, base = 1ll * base * base % mod)
        if (p & 1) ret = 1ll * ret * base % mod;
    return ret;
}

int fac[maxn], inv[maxn], c[maxn];

int C(int n, int m) {
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    read(t);
    int N = 2e5;
    fac[0] = 1;
    FOR(i, 1, N) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[N] = qPow(fac[N], mod - 2);
    DEC(i, N - 1, 0) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
    while (t--) {
        read(n), read(k);
        int X = 0;
        for (int i = 0; i < n; i += 2) X = (X + C(n, i)) % mod;
        int c = 1, ans = 0;
        FOR(i, 1, k) {
            if (!(n & 1)) ans = (ans + 1ll * c * qPow(qPow(2, k - i), n) % mod) % mod;
            c = 1ll * c * (X + (n & 1)) % mod;
        }
        ans = (ans + c) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
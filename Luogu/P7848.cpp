#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define il inline

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

typedef long long ll;
typedef unsigned long long ull;

const int mod = 998244353;

const int maxn = 1 << 17 | 500;

ll qPow(ll a, ll b = mod - 2) {
    a %= mod;
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ret = a * ret % mod;
    return ret;
}

int tr[maxn << 1], revLim;
void getTr(int n) {
    if (revLim == n) return;
    revLim = n;
    FOR(i, 0, n - 1)
        tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
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
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

int f[maxn];

int main() {
    ll n, k; read(n), read(k);
    n = 1ll << n;
    FOR(i, 0, n - 1) read(f[i]);
    ll tmp = qPow(n * n, k / 4);
    FOR(i, 0, n - 1) f[i] = 1ll * f[i] * tmp % mod;
    FOR(i, 1, k % 4) DFT(f, 1, n);
    FOR(i, 0, n - 1) print(f[i]), putchar(' ');
    return output(), 0;
}
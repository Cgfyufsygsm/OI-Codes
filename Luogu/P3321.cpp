#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

typedef long long ll;
typedef unsigned long long ull;

const int mod = 1004535809;

const int maxn = 1 << 17 | 500;

ll qPow(ll a, ll b = mod - 2) {
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

int n, m, x, S;
int a[8005], Log[8005];
int f[maxn], ans[maxn];

bool check(int g, int m) {
    int vis[8005] = {0};
    for (int i = 0, tmp = 1; i < m - 1; ++i, tmp = 1ll * tmp * g % m) {
        ++vis[tmp];
        if (vis[tmp] > 1) return 0;
    }
    return 1;
}

void getG(int m) {
    int g;
    FOR(i, 2, m - 1) {
        if (check(i, m)) {
            g = i;
            break;
        }
    }
    for (int i = 0, tmp = 1; i < m - 1; ++i, tmp = 1ll * tmp * g % m)
        Log[tmp] = i;
    return;
}

int lim;

int main() {
    read(n), read(m), read(x), read(S);
    for (lim = 1; lim < m; lim <<= 1); lim <<= 1;
    getG(m);
    FOR(i, 1, S) {
        int a; read(a), a %= m;
        if (!a) continue;
        f[Log[a]] = 1;
    }
    ans[0] = 1;
    for (; n; n >>= 1) {
        DFT(f, 1, lim);
        if (n & 1) {
            DFT(ans, 1, lim);
            FOR(i, 0, lim - 1) ans[i] = 1ll * ans[i] * f[i] % mod;
            DFT(ans, 0, lim);
            DEC(i, lim - 1, m - 1) ans[i - m + 1] = (ans[i] + ans[i - m + 1]) % mod, ans[i] = 0;
        }
        FOR(i, 0, lim - 1) f[i] = 1ll * f[i] * f[i] % mod;
        DFT(f, 0, lim);
        DEC(i, lim - 1, m - 1) f[i - m + 1] = (f[i] + f[i - m + 1]) % mod, f[i] = 0;
    }
    print(ans[Log[x]]);
    return output(), 0;
}
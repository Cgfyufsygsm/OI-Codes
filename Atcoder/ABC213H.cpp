#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
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

const int mod = 998244353;

namespace polynomial {
const int maxn = 1 << 17 | 500;
typedef std::vector<int> Poly;
const Poly one(1, 1);

ll qPow(ll a, ll b = mod - 2) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ret = a * ret % mod;
    return ret;
}

int tr[maxn << 1], revLim, lim;
void getTr(int n) {
    if (revLim == n) return;
    revLim = n;
    FOR(i, 0, n - 1)
        tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
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

void mul(int *f, int *g, int n) {
    FOR(i, 0, n - 1) f[i] = 1ll * f[i] * g[i] % mod;
    return;
}

Poly operator*(const Poly &A, const Poly &B) {
    static int a[maxn << 1], b[maxn << 1];
    cpy(a, &A[0], A.size());
    cpy(b, &B[0], B.size());
    Poly C; C.resize(min(lim, (int)(A.size() + B.size() - 1)));
    int n = 1; for (n = 1; n < (int)(A.size() + B.size() - 1); n <<= 1);
    DFT(a, 1, n), DFT(b, 1, n);
    mul(a, b, n), DFT(a, 0, n);
    cpy(&C[0], a, C.size());
    clr(a, n), clr(b, n);
    return C;
}
} // namespace polynomial

using namespace polynomial;
// warning: don't forget to set lim

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
} // namespace fastIO

using namespace fastIO;

Poly f[11], p[11], t1, t2;
int n, m, T, u[11], v[11];

void solve(Poly &f, Poly &g, Poly &ret, int l, int r) {
    int mid = (l + r) >> 1;
    t1 = {f.begin() + l, f.begin() + mid + 1};
    t2 = {g.begin() + 1, g.begin() + r - l + 1};
    t1 = t1 * t2;
    FOR(i, mid + 1, r) ret[i] = (ret[i] + t1[i - l - 1]) % mod;
    return;
}

void solve(int l, int r) {
    int mid = (l + r) >> 1;
    if (l == r) return;
    solve(l, mid);
    FOR(i, 1, m) {
        solve(f[u[i]], p[i], f[v[i]], l, r);
        solve(f[v[i]], p[i], f[u[i]], l, r);
    }
    solve(mid + 1, r);
    return;
}

int main() {
    read(n), read(m), read(T);
    lim = T + 1;
    FOR(i, 1, m) {
        read(u[i]), read(v[i]);
        p[i].resize(T + 1);
        FOR(j, 1, T) read(p[i][j]);
    }
    FOR(i, 1, n) f[i].resize(T + 1);
    f[1][0] = 1;
    solve(0, T);
    print(f[1][T]);
    return output(), 0;
}
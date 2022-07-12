#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define VEC(i, v) for (int i = 0; i < (int)v.size(); ++i)
#define il inline
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

using namespace std;

namespace YangTY {

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

using ll = long long;
using ull = unsigned long long;

const int mod = 998244353;

namespace polynomial {
const int maxn = 1 << 17 | 500;
using Poly = vector<int>;
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

int inv[maxn], fac[maxn], ifac[maxn];
void initInv() {
    inv[1] = 1;
    FOR(i, 2, lim) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    fac[0] = 1;
    FOR(i, 1, lim) fac[i] = 1ll * i * fac[i - 1] % mod;
    ifac[lim] = qPow(fac[lim]);
    DEC(i, lim - 1, 0) ifac[i] = (i + 1ll) * ifac[i + 1] % mod;
    return;
}
} // namespace polynomial

using namespace polynomial;
// warning: don't forget to set lim

Poly e, f, g;
int q[maxn];

int main() {
    int T; cin >> T;
    FOR(i, 1, T) {
        int n; cin >> n;
        q[i] = n, lim = max(lim, n + 1);
    }
    initInv();
    e.resize(lim);
    FOR(i, 0, lim - 1) e[i] = ifac[i];
    f.push_back(2);
    f = polyInv(f - e);
    g = f * f * (e - one);
    FOR(i, 1, T) cout << 1ll * g[q[i]] * qPow(f[q[i]]) % mod << '\n';
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
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
}

using namespace fastIO;

typedef long long ll;
const ll mod = 1000000007;
const int maxn = 1e6 + 5;

ll qPow(ll a, ll b, ll p = mod) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ret = ret * a % mod;
    return ret;
}

il ll inv(ll x) {return qPow(x, mod - 2);}

ll fac[maxn << 1], facinv[maxn << 1];

il ll catalan(int x) {
    return fac[x << 1] * facinv[x] % mod * facinv[x] % mod * inv(x + 1) % mod;
}

struct node {
    int minv, fir, cnt;
} t[maxn << 2];

int a[maxn], n;
ll ans = 0;

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

node operator+(const node &a, const node &b) {
    node ret;
    if (a.minv < b.minv) {
        ret.minv = a.minv;
        ret.fir = a.fir;
        ret.cnt = a.cnt;
    } else if (a.minv == b.minv) {
        ret.minv = a.minv;
        ret.fir = a.fir;
        ret.cnt = a.cnt + b.cnt;
    } else {
        ret.minv = b.minv;
        ret.fir = b.fir;
        ret.cnt = b.cnt;
    }
    return ret;
}

void build(int i, int j, int k) {
    if (i > j) return;
    if (i == j) {
        t[k].minv = a[i];
        t[k].cnt = 1;
        t[k].fir = i;
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    t[k] = t[L] + t[R];
    return;
}

node query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    if (y <= M) return query(i, M, L, x, y);
    if (x > M) return query(M + 1, j, R, x, y);
    return query(i, M, L, x, y) + query(M + 1, j, R, x, y);
}

ll solve(int l, int r) {
    ll ret = 1;
    if (l >= r) return ret;
    node now = query(1, n, 1, l, r);
    int x = l, y = now.fir, curmin = now.minv;
    ret = ret * catalan(now.cnt) % mod;
    while (x <= r) {
        ret = ret * solve(x, y - 1) % mod;
        if (y == r) break;
        now = query(1, n, 1, y + 1, r);
        if (now.minv != curmin) break;
        x = y + 1, y = now.fir;
    }
    ret = ret * solve(y + 1, r) % mod;
    return ret;
}

int main() {
    int up = 2e6;
    fac[0] = 1;
    FOR(i, 1, up) fac[i] = i * fac[i - 1] % mod;
    facinv[up] = inv(fac[up]);
    DEC(i, up - 1, 0) facinv[i] = facinv[i + 1] * (i + 1) % mod;

    read(n);
    FOR(i, 1, n) read(a[i]);
    build(1, n, 1);
    printf("%lld\n", solve(1, n));
    return 0;
}
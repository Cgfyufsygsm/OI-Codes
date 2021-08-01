#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <ctime>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

il ll mul(ll a, ll b, ll mod) {return (a * b - (ll)((long double)a / mod * b) * mod + mod) % mod;}

ll qPow(ll base, ll p, ll mod) {
    ll ret = 1;
    for (; p; p >>= 1, base = mul(base, base, mod))
        if (p & 1) ret = mul(ret, base, mod);
    return ret;
}

bool millerRabin(ll n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    ll u = n - 1, t = 0;
    while (u % 2 == 0) u /= 2, ++t;
    FOR(i, 1, 10) {
        ll a = rand() % (n - 2) + 2, v = qPow(a, u, n);
        if (v == 1) continue;
        int j;
        for (j = 0; j < t; ++j) {
            if (v == n - 1) break;
            v = mul(v, v, n);
        }
        if (j >= t) return 0;
    }
    return 1;
}

il ll f(ll x, ll c, ll n) {return (mul(x, x, n) + c) % n;}
il ll myabs(ll x) {return x >= 0 ? x : -x;}
il ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
il ll max(ll a, ll b) {return a > b ? a : b;}

ll pollardRho(ll n) {
    ll s = 0, t = 0;
    ll c = (ll)rand() % (n - 1) + 1;
    ll val = 1;
    for (int goal = 1;; goal <<= 1, s = t, val = 1) {
        FOR(step, 1, goal) {
            t = f(t, c, n);
            val = mul(val, myabs(t - s), n);
            if (step % 127 == 0) {
                ll d = gcd(val, n);
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, n);
        if (d > 1) return d;
    }
}

ll ans;

void work(ll n) {
    if (n <= ans || n < 2) return;
    if (millerRabin(n)) {
        ans = max(ans, n);
        return;
    }
    ll p = n;
    while (p >= n) p = pollardRho(n);
    while (n % p == 0) n /= p;
    work(n), work(p);
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        srand(time(0));
        ll n; read(n);
        ans = 0;
        work(n);
        if (ans == n) puts("Prime");
        else printf("%lld\n", ans);
    }
    return 0;
}
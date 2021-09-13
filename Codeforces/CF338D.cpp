#include <cstdio>
#include <cctype>
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

typedef long long ll;

ll n, m, k, a[10005], mod[10005], r[10005];

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll tmp = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return tmp;
}

il ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}

typedef long double ldb;

il ll mul(ll a, ll b, ll mod) {
    return (a * b - (ll)((ldb)a / mod * b) * mod + mod) % mod;
}

ll exCRT(ll *r, ll *m, int n) {
    for (int i = 2; i <= n; ++i) {
        ll tmpx, tmpy;
        ll gcd = exgcd(m[i], m[i - 1], tmpx, tmpy);
        ll p1 = m[i - 1] / gcd, p2 = m[i] / gcd;
        exgcd(p1, p2, tmpx, tmpy);
        m[i] = m[i] / gcd * m[i - 1];
        r[i] = (r[i - 1] + mul(m[i - 1], mul((r[i] - r[i - 1]) / gcd, tmpx, m[i]), m[i])) % m[i];
    }
    return (r[n] + m[n] - 1) % m[n] + 1;
}

int main() {
    read(n), read(m), read(k);
    ll x = 1;
    FOR(i, 1, k) {
        read(a[i]);
        x = x / gcd(x, a[i]) * a[i];
        if (x > n) return puts("NO"), 0;
        r[i] = ((a[i] + 1 - i) % a[i] + a[i]) % a[i];
        mod[i] = a[i];
    }
    ll y = exCRT(r, mod, k);
    if (y + k - 1 > m || y < 1) return puts("NO"), 0;
    FOR(i, 1, k) if (gcd(x, y + i - 1) != a[i]) return puts("NO"), 0;
    return puts("YES"), 0;
}
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

typedef long long ll;
const ll mod = 998244353, inv2 = 499122177, inv6 = 166374059;

struct query {
    ll f, g, h;
};

il ll S1(ll n) {return n * (n + 1) / 2 % mod;}
il ll S2(ll n) {return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;}

query calc(ll a, ll b, ll c, ll n) {
    query ret;
    ll s1, s2, ac, bc;
    ll m;
    ac = a / c, bc = b / c, s1 = S1(n), s2 = S2(n), m = (a * n + b) / c;
    if (a == 0) {
        ret.f = bc * (n + 1) % mod;
        ret.g = bc * s1 % mod;
        ret.h = bc * bc % mod * (n + 1) % mod;
    } else if (a >= c || b >= c) {
        auto pre = calc(a % c, b % c, c, n);
        ret.f = (s1 * ac % mod + (n + 1) * bc % mod + pre.f) % mod;
        ret.g = (ac * s2 % mod + bc * s1 % mod + pre.g) % mod;
        ret.h = (ac * ac % mod * s2 + 2 * s1 * ac % mod * bc % mod + (n + 1) * bc % mod * bc % mod + 2 * ac * pre.g % mod + 2 * bc * pre.f % mod + pre.h) % mod;
    } else {
        auto pre = calc(c, c - b - 1, a, m - 1);
        ret.f = (n * m % mod + mod - pre.f) % mod;
        ret.g = (m * n % mod * (n + 1) % mod + mod - pre.h + mod - pre.f) % mod * inv2 % mod;
        ret.h = (n * m % mod * (m + 1) % mod + mod - 2 * pre.g % mod + mod - 2 * pre.f % mod + mod - ret.f) % mod;
    }
    return ret;
}

int main() {
    int T; read(T);
    while (T--) {
        int a, b, c, n; read(n), read(a), read(b), read(c);
        query ans = calc(a, b, c, n);
        print(ans.f), putchar(' '), print(ans.h), putchar(' '), print(ans.g), putchar('\n');
    }
    return output(), 0;
}
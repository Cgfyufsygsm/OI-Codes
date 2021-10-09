#include <cstdio>
#include <cctype>
#include <cmath>
#include <vector>
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
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
using ldb = long double;

ll getphi(ll n) {
    ll ans = n, sq = sqrt(n);
    FOR(i, 2, sq) {
        if (n % i) continue;
        ans = ans / i * (i - 1);
        while (n % i == 0) n /= i;
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

il ll mul(ll a, ll b, ll mod) {
    return (a * b - (ll)((ldb)a / mod * b) * mod + mod) % mod;
}

ll qPow(ll a, ll b, ll p) {
    ll ret = 1;
    a %= p;
    for (; b; b >>= 1, a = mul(a, a, p))
        if (b & 1) ret = mul(ret, a, p);
    return ret;
}

std::vector<ll> fact;

int main() {
    int T; read(T);
    while (T--) {
        ll k; read(k);
        ll mod = 9 * k;
        if (k % 2 == 0) mod /= 2;
        ll phi = getphi(mod), sphi = sqrt(phi);
        FOR(i, 1, sphi) {
            if (phi % i == 0) {
                fact.push_back(i);
                if (phi / i != i)
                    fact.push_back(phi / i);
            }
        }
        std::sort(fact.begin(), fact.end());
        ll ans = -1;
        for (auto res : fact) {
            if (qPow(10, res, mod) == 1) {
                ans = res;
                break;
            }
        }
        print(ans, '\n');
    }
    return output(), 0;
}
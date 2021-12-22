#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
ll n, m, mod;

void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x), y -= a / b * x;
    return;
}

il ll inv(ll n, ll mod) {
    ll x, y;
    exgcd(n, mod, x, y);
    return (x + mod) % mod;
}

ll qPow(ll base, ll exp, ll mod) {
    ll ret = 1;
    for (; exp; exp >>= 1, base = base * base % mod)
        if (exp & 1) ret = ret * base % mod;
    return ret;
}

ll CRT(int n, ll *a, ll *m) {
    ll M = 1, ret = 0;
    FOR(i, 1, n) M *= m[i];
    FOR(i, 1, n) {
        ll w = M / m[i];
        ret = (ret + a[i] * w % mod * inv(w, m[i]) % mod) % mod;
    }
    return (ret + mod) % mod;
}

ll f(ll n, ll p, ll pk) {
    if (!n) return 1;
    ll ret = 1;
    FOR(i, 1, pk) if (i % p) ret = ret * i % pk;
    ret = qPow(ret, n / pk, pk);
    for (ll i = n / pk * pk + 1; i <= n; ++i)
        if (i % p) ret = ret * (i % pk) % pk;
    return ret * f(n / p, p, pk) % pk;
}

ll multiLucas(ll n, ll m, ll p, ll pk) {
    int cnt = 0;
    for (ll i = n; i; i /= p) cnt += i / p;
    for (ll i = m; i; i /= p) cnt -= i / p;
    for (ll i = n - m; i; i /= p) cnt -= i / p;
    return qPow(p, cnt, pk) * f(n, p, pk) % pk * inv(f(m, p, pk), pk) % pk * inv(f(n - m, p, pk), pk) % pk;
}


ll exLucas(ll n, ll m, ll p) {
    int cnt = 0;
    ll pk[20], a[20];
    for (ll i = 2; i * i <= p; ++i) {
        if (p % i == 0) {
            pk[++cnt] = 1;
            while (p % i == 0) pk[cnt] *= i, p /= i;
            a[cnt] = multiLucas(n, m, i, pk[cnt]);
        }
    }
    if (p > 1) pk[++cnt] = p, a[cnt] = multiLucas(n, m, p, p);
    return CRT(cnt, a, pk);
}

int main() {
    read(n, m, mod);
    print(exLucas(n, m, mod));
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
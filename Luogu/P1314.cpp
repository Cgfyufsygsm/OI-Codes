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
const int maxn = 2e5 + 5, maxw = 1e6 + 5;
const ll INF = 2e18;

int n, m, L[maxn], R[maxn];
ll s, w0[maxn], v0[maxn], w[maxn], v[maxn];

il ll min(const ll &a, const ll &b) {return a < b ? a : b;}

int main() {
    read(n), read(m), read(s);
    FOR(i, 1, n) read(w0[i]), read(v0[i]);
    FOR(i, 1, m) read(L[i]), read(R[i]);
    ll l = 0, r = 1e6 + 2, ans = 1e18;
    while (l < r) {
        ll W = (l + r) >> 1;
        FOR(i, 1, n) w[i] = (w0[i] >= W) + w[i - 1], v[i] = (w0[i] >= W ? v0[i] : 0) + v[i - 1];
        ll ret = 0;
        FOR(i, 1, m) ret += (w[R[i]] - w[L[i] - 1]) * (v[R[i]] - v[L[i] - 1]);
        if (ret <= s) ans = min(ans, s - ret), r = W;
        else ans = min(ans, ret - s), l = W + 1;
    }
    print(ans);
    return output(), 0;
}
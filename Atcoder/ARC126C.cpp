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
const int maxn = 3e5 + 5, N = 6e5;
int n, a[maxn], maxa;
ll k, sum[maxn << 1], vis[maxn << 1];

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

int main() {
    read(n), read(k);
    FOR(i, 1, n) read(a[i]), ++vis[a[i]], maxa = max(maxa, a[i]);
    FOR(i, 1, N) sum[i] = sum[i - 1] + 1ll * vis[i] * i, vis[i] += vis[i - 1];
    ll ans = 1;
    FOR(x, 2, maxa) {
        ll cost = 0;
        for (int xx = x; xx <= N; xx += x)
            cost += (vis[xx] - vis[xx - x]) * xx - (sum[xx] - sum[xx - x]);
        if (cost <= k) ans = x;
        if (x == maxa && cost <= k) {
            k -= cost;
            ans = x + k / n;
        }
    }
    print(ans);
    return output(), 0;
}
#include <cstdio>
#include <cctype>
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

const int maxn = 1e3 + 5, maxm = 1e4 + 5;
typedef long long ll;
int n, m, k;
ll maxt[maxn], D[maxn], T[maxm], A[maxm], B[maxm], t[maxn], arrive[maxn], f[maxn];

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

int main() {
    read(n), read(m), read(k);
    FOR(i, 1, n - 1) read(D[i]);
    FOR(i, 1, m)
        read(T[i]), read(A[i]), read(B[i]), maxt[A[i]] = max(maxt[A[i]], T[i]), ++arrive[B[i]];
    FOR(i, 2, n) t[i] = max(maxt[i - 1], t[i - 1]) + D[i - 1], arrive[i] += arrive[i - 1];
    ll ans = 0;
    FOR(i, 1, m) ans += t[B[i]] - T[i];
    while (k--) {
        f[n - 1] = f[n] = n;
        DEC(i, n - 2, 1) {
            if (t[i + 1] > maxt[i + 1])
                f[i] = f[i + 1];
            else f[i] = i + 1;
        }
        ll maxx = 0, pos = 0;
        FOR(i, 1, n - 1)
            if (maxx < arrive[f[i]] - arrive[i] && D[i]) maxx = arrive[f[i]] - arrive[i], pos = i;
        if (!pos) break;
        ans -= maxx, --D[pos];
        FOR(i, pos, n) t[i] = max(maxt[i - 1], t[i - 1]) + D[i - 1];
    }
    print(ans);
    return output(), 0;
}
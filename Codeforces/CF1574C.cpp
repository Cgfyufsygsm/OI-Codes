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

typedef long long ll;

const int maxn = 2e5 + 5;
int n, m;
ll a[maxn], sum;

template<typename T> il T min(T a, T b) {return a < b ? a : b;}
template<typename T> il T max(T a, T b) {return a > b ? a : b;}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]), sum += a[i];
    std::sort(a + 1, a + n + 1);
    int tot = std::unique(a + 1, a + n + 1) - a - 1;
    read(m);
    FOR(i, 1, m) {
        ll x, y, ans = 2e18; read(x), read(y);
        if (x < a[1]) ans = min(ans, max(y - sum + a[1], 0ll));
        else if (x > a[tot]) ans = min(ans, x - a[tot] + max(y - sum + a[tot], 0ll));
        else {
            ll* p = std::lower_bound(a + 1, a + tot + 1, x);
            if (p - 1 >= a + 1) {
                ans = min(ans, max(x - *(p - 1), 0ll) + max(y - sum + *(p - 1), 0ll));
            }
            if (p + 1 <= a + tot) {
                ans = min(ans, max(x - *(p + 1), 0ll) + max(y - sum + *(p + 1), 0ll));
            }
            ans = min(ans, max(x - *p, 0ll) + max(y - sum + *p, 0ll));
        }
        print(ans), putchar('\n');
    }
    return output(), 0;
}
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

ll T, n2, n3, n4;
il ll min(ll a, ll b) {return a < b ? a : b;}

int main() {
    read(T);
    while (T--) {
        read(n2), read(n3), read(n4);
        ll ans = 0;
        ll k1 = min(n3 / 2, n4);
        ans += k1, n3 -= 2 * k1, n4 -= k1;
        ll k2 = min(n4 / 2, n2);
        ans += k2, n4 -= 2 * k2, n2 -= k2;
        ll k3 = min(n4, n2 / 3);
        ans += k3, n3 -= 3 * k3, n4 -= k3;
        ll k4 = min(n2 / 2, n3 / 2);
        ans += k4, n2 -= 2 * k4, n3 -= 2 * k4;
        ans += n2 / 5;
        print(ans), putchar('\n');
    }
    return output(), 0;
}
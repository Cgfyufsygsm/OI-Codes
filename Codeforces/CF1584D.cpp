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

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
ll n;

ll ask(ll a, ll b) {
    printf("? %lld %lld\n", a, b);
    fflush(stdout);
    ll res;
    scanf("%lld", &res);
    return res;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        ll ansi, ansj, ansk;
        ll l = 1, r = n + 1;
        ll sum = ask(1, n);
        while (l < r) {
            ll mid = (l + r) >> 1;
            ll tmp = ask(1, mid);
            if (!tmp) {
                ansi = mid;
                l = mid + 1;
            } else r = mid;
        }
        ll sum2 = ask(ansi + 1, n);
        ll p2 = sum - sum2 + 1;
        ll sum3 = sum - p2 * (p2 - 1) / 2;
        l = 1, r = n + 1;
        //printf("tmp p2 %d %d %d\n", p2, sum, sum2);
        while (l < r) {
            ll mid = (l + r) >> 1;
            ll tmp = mid * (mid - 1) / 2;
            if (tmp == sum3) {
                ansj = ansi + p2;
                ansk = ansj + mid - 1;
                break;
            }
            if (tmp < sum3) l = mid + 1;
            else r = mid;
        }
        printf("! %lld %lld %lld\n", ansi, ansj, ansk);
        fflush(stdout);
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
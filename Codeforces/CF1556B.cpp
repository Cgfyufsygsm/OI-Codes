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

const int maxn = 1e5 + 5;
int n, a[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        int cnt = 0;
        FOR(i, 1, n) read(a[i]), a[i] &= 1, cnt += a[i];
        if (cnt != n / 2 && cnt != (n + 1) / 2) {
            print(-1, '\n');
            continue;
        }
        long long ans = 0;
        if (!(n & 1)) {
            int now = 1;
            FOR(i, 1, n) if (a[i] & 1) ans += myabs(i - now), now += 2;
            now = 2;
            long long tmp = 0;
            FOR(i, 1, n) if (a[i] & 1) tmp += myabs(i - now), now += 2;
            ans = min(ans, tmp);
        } else {
            int now;
            if (cnt == n / 2) now = 2; else now = 1;
            FOR(i, 1, n) if (a[i] & 1) ans += myabs(i - now), now += 2;
        }
        print(ans, '\n');
    }
    return output(), 0;
}
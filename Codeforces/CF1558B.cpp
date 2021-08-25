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

const int maxn = 4e6 + 5;
int n, mod, f[maxn], d[maxn], sum[maxn];

il int min(int a, int b) {return a < b ? a : b;}

int main() {
    read(n), read(mod);
    FOR(i, 1, n) {
        d[i] = (d[i - 1] + d[i]) % mod, f[i] = (sum[i - 1] + d[i]) % mod;
        if (i == 1) f[i] = 1;
        for (int j = 2; i * j <= n; ++j)
            d[i * j] = (d[i * j] + f[i]) % mod, d[min((i + 1) * j, n + 1)] = (d[min((i + 1) * j, n + 1)] - f[i] + mod) % mod;
        sum[i] = (sum[i - 1] + f[i]) % mod;
    }
    printf("%d\n", f[n]);
    return output(), 0;
}
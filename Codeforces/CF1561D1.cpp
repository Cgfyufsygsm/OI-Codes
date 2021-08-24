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
}

using namespace fastIO;

const int maxn = 1e6 + 5;
int n, mod;
int f[maxn], sum[maxn];

int main() {
    read(n), read(mod);
    f[1] = sum[1] = 1;
    FOR(i, 2, n) {
        f[i] = sum[i - 1];
        for (int l = 2, r; l <= i; l = r + 1) {
            r = i / (i / l);
            f[i] = (f[i] + 1ll * (r - l + 1) * f[i / l] % mod) % mod;
        }
        sum[i] = (sum[i - 1] + f[i]) % mod;
    }
    print(f[n]);
    return output(), 0;
}

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

const int mod = 10007;
int n, m, a, b, k, binom[1005][1005];

int qPow(int base, int exp) {
    int ret = 1;
    for (; exp; exp >>= 1, base = 1ll * base * base % mod)
        if (exp & 1) ret = 1ll * ret * base % mod;
    return ret;
}

int main() {
    read(a), read(b), read(k), read(n), read(m);
    binom[1][1] = binom[1][0] = 1;
    FOR(i, 2, 1000) {
        binom[i][0] = binom[i][i] = 1;
        FOR(j, 1, i - 1) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }
    printf("%d\n", 1ll * qPow(a, n) * qPow(b, m) % mod * binom[k][n] % mod);
    return output(), 0;
}
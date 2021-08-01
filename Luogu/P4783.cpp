#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
    void printStr(const char *s) {
        for (int i = 0; s[i]; ++i)
            putchar(s[i]);
        return;
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

const int maxn = 405, mod = 1e9 + 7;

int n, a[maxn][maxn << 1];

int qPow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1) ret = 1ll * ret * a % mod;
    return ret;
}

int main() {
    read(n);
    FOR(i, 1, n) {
        FOR(j, 1, n) read(a[i][j]);
        a[i][i + n] = 1;
    }

    FOR(i, 1, n) {
        int r = i;
        FOR(j, i + 1, n)
            if (a[j][i] > a[r][i])
                r = j;
        if (r != i) std::swap(a[r], a[i]);
        if (!a[i][i]) {
            printStr("No Solution\n");
            return output(), 0;
        }
        int div = qPow(a[i][i], mod - 2);
        FOR(k, 1, n) {
            if (k == i) continue;
            int p = 1ll * a[k][i] * div % mod;
            FOR(j, 1, n << 1)
                a[k][j] = ((a[k][j] - 1ll * p * a[i][j] % mod) % mod + mod) % mod;
        }
        FOR(j, 1, n << 1) a[i][j] = 1ll * a[i][j] * div % mod;
    }

    FOR(i, 1, n) {
        FOR(j, n + 1, n << 1)
            print(a[i][j]), putchar(' ');
        putchar('\n');
    }
    return output(), 0;
}
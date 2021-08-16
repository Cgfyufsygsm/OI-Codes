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

const int maxn = 1e4 + 5;
int n, a[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        if (a[1] == 1) {
            print(n + 1), putchar(' ');
            FOR(i, 1, n) print(i), putchar(' ');
            putchar('\n');
        } else if (a[n] == 0) {
            FOR(i, 1, n + 1) print(i), putchar(' ');
            putchar('\n');
        } else {
            int pos = -1;
            for (int i = 1; i < n; ++i) {
                if (a[i] == 0 && a[i + 1] == 1) {
                    pos = i;
                    break;
                }
            }
            FOR(i, 1, pos) print(i), putchar(' ');
            print(n + 1), putchar(' ');
            FOR(i, pos + 1, n) print(i), putchar(' ');
            putchar('\n');
        }
    }
    return output(), 0;
}
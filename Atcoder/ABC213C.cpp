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

const int maxn = 1e5 + 5;

int h, w, n;
struct Point {
    int x, y;
} p[maxn];

int x[maxn], y[maxn];

int main() {
    read(h), read(w), read(n);
    FOR(i, 1, n) read(p[i].x), read(p[i].y), x[i] = p[i].x, y[i] = p[i].y;
    //FOR(i, 1, n) printf("%d\n", x[i]);
    std::sort(x + 1, x + n + 1);
    std::sort(y + 1, y + n + 1);
    int totx, toty;
    totx = std::unique(x + 1, x + n + 1) - x - 1;
    toty = std::unique(y + 1, y + n + 1) - y - 1;
    FOR(i, 1, n) {
        print(std::lower_bound(x + 1, x + totx + 1, p[i].x) - x), putchar(' ');
        print(std::lower_bound(y + 1, y + toty + 1, p[i].y) - y), putchar('\n');
    }
    return output(), 0;
}
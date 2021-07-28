#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

il int min(int a, int b) {return a < b ? a : b;}
il int max(int a, int b) {return a > b ? a : b;}

const int maxn = 205;
int f1[maxn][maxn], f2[maxn][maxn], s[maxn][maxn], a[maxn], n;

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]), a[i + n] = a[i];
    FOR(i, 1, n << 1) a[i] += a[i - 1], f1[i][i] = 0, f2[i][i] = 0, s[i][i] = i;
    FOR(len, 2, n) {
        for (int i = 1, j = i + len - 1; j <= n << 1; ++i, ++j) {
            f2[i][j] = max(f2[i + 1][j], f2[i][j - 1]) + a[j] - a[i - 1];
            f1[i][j] = 1 << 30;
            FOR(k, s[i][j - 1], s[i + 1][j]) {
                if (f1[i][j] > f1[i][k] + f1[k + 1][j] + a[j] - a[i - 1])
                    f1[i][j] = f1[i][k] + f1[k + 1][j] + a[j] - a[i - 1], s[i][j] = k;
            }
        }
    }
    int ansmn = 1 << 30, ansmx = 0;
    FOR(i, 1, n) ansmn = min(f1[i][i + n - 1], ansmn), ansmx = max(f2[i][i + n - 1], ansmx);
    print(ansmn), putchar('\n'), print(ansmx);
    return output(), 0;
}
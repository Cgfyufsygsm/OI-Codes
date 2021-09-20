#include <cstdio>
#include <cctype>
#include <cstring>
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

const int maxn = 505;
int n, x, y, a[maxn], b[maxn];
int f[2][maxn][maxn];
// f[i][j][k] 前 i 个午餐盒，当前 a 有 j 个，b 有 k 个的最小

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

int main() {
    read(n), read(x), read(y);
    FOR(i, 1, n) read(a[i]), read(b[i]);
    memset(f, 0x3f, sizeof f);
    f[0][0][0] = 0;
    FOR(i, 1, n) {
        FOR(j, 0, x) {
            FOR(k, 0, y) {
                int tj = min(j + a[i], x), tk = min(k + b[i], y);
                f[i & 1][j][k] = min(f[i & 1][j][k], f[(i - 1) & 1][j][k]);
                f[i & 1][tj][tk] = min(f[i & 1][tj][tk], f[(i - 1) & 1][j][k] + 1);
            }
        }
    }
    print(f[n & 1][x][y] > n ? -1 : f[n & 1][x][y]);
    return output(), 0;
}
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
typedef long long ll;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int maxn = 1e3 + 5;
ll a[maxn][maxn], f[maxn][maxn][3];
int n, m;

int main() {
    read(n), read(m);
    FOR(i, 1, n) FOR(j, 1, m) read(a[i][j]);
    memset(f, 0x80, sizeof f);
    f[1][1][0] = f[1][1][2] = a[1][1];
    FOR(j, 1, m) {
        FOR(i, 1, n) {
            if (i == 1 && j == 1) continue;
            FOR(k, 0, 2) f[i][j][0] = max(f[i][j][0], f[i][j - 1][k] + a[i][j]);
            f[i][j][2] = max(f[i - 1][j][0], f[i - 1][j][2]) + a[i][j];
        }
        FOR(i, 2, n) f[i][j][2] = max(f[i - 1][j][0], f[i - 1][j][2]) + a[i][j];
        DEC(i, n - 1, 1) {
            if (i == j && j == 1) continue;
            f[i][j][1] = max(f[i + 1][j][0], f[i + 1][j][1]) + a[i][j];
        }
    }
    print(max(f[n][m][0], max(f[n][m][1], f[n][m][2])));
    return output(), 0;
}
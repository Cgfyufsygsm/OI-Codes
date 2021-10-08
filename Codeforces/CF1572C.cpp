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

const int maxn = 3e3 + 5;
int n, a[maxn], pos[maxn], last[maxn], f[maxn][maxn];

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

int main() {
    int T; read(T);
    while (T--) {
        int m; read(m);
        FOR(i, 1, m) read(a[i]), pos[a[i]] = 0;
        n = 0;
        FOR(j, 1, m) if (a[j] != a[j - 1]) a[++n] = a[j];
        FOR(i, 1, n) {
            last[i] = 0;
            if (pos[a[i]]) last[i] = pos[a[i]];
            pos[a[i]] = i;
        }
        FOR(i, 1, n) FOR(j, 1, n) f[i][j] = 1e9;
        FOR(i, 1, n) f[i][i] = f[i + 1][i] = 0;
        FOR(len, 2, n) {
            for (int i = 1, j = i + len - 1; j <= n; ++i, ++j) {
                f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
                for (int k = last[j]; k >= i; k = last[k])
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
        print(f[1][n], '\n');
    }
    return output(), 0;
}
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

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 1005;
int a[maxn][maxn], n, m, q;
ll tot, f[maxn][maxn], g[maxn][maxn], ans;

int main() {
    read(n), read(m), read(q);
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            f[i][j] = 1 + g[i - 1][j];
            g[i][j] = 1 + f[i][j - 1];
            ans += f[i][j] + g[i][j];
            a[i][j] = 1;
        }
    }
    tot = n * m;
    while (q--) {
        int x, y; read(x), read(y);
        if (a[x][y]) {
            ans -= f[x][y] + g[x][y];
            f[x][y] = g[x][y] = 0;
            ans += f[x][y] + g[x][y];
            --tot;
        } else {
            ans -= f[x][y] + g[x][y];
            f[x][y] = g[x][y] = 1;
            if (x > 1) f[x][y] += g[x - 1][y];
            if (y > 1) g[x][y] += f[x][y - 1];
            ans += f[x][y] + g[x][y];
            ++tot;
        }
        a[x][y] ^= 1;
        for (; x <= n && y <= m; ++x, ++y) {
            if (x < n) {
                ans -= f[x + 1][y];
                f[x + 1][y] = a[x + 1][y] * (1 + g[x][y]);
                ans += f[x + 1][y];
            }
            if (y < m) {
                ans -= g[x][y + 1];
                g[x][y + 1] = a[x][y + 1] * (1 + f[x][y]);
                ans += g[x][y + 1];
            }
            if (x < n && y < m) {
                ans -= f[x + 1][y + 1] + g[x + 1][y + 1];
                f[x + 1][y + 1] = a[x + 1][y + 1] * (1 + g[x][y + 1]);
                g[x + 1][y + 1] = a[x + 1][y + 1] * (1 + f[x + 1][y]);
                ans += f[x + 1][y + 1] + g[x + 1][y + 1];
            }
        }
        print(ans - tot, '\n');
    }
    return output(), 0;
}
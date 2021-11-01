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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}

using ll = long long;
const int maxn = 1e5 + 5, sqrtn = 500, INF = 2e9;
int n, a[maxn];
ll sum[maxn], f[maxn][sqrtn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]), sum[i] = sum[i - 1] + a[i];
        int k = 0;
        while (k * (k + 1) / 2 <= n) ++k;
        --k;
        FOR(j, 0, k) f[n + 1][j] = -INF;
        f[n + 1][0] = INF;
        DEC(i, n, 1) {
            FOR(j, 0, k) {
                f[i][j] = f[i + 1][j];
                if (j && i + j - 1 <= n && sum[i + j - 1] - sum[i - 1] < f[i + j][j - 1])
                    chkmax(f[i][j], sum[i + j - 1] - sum[i - 1]);
            }
        }
        int ans = 0;
        FOR(j, 0, k) if (f[1][j] > 0) ans = j;
        print(ans, '\n');
    }
    return output(), 0;
}
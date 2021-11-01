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

const int maxn = 1005, INF = 0x3f3f3f3f;
int a[maxn], b[maxn], n;
int f[maxn][(1 << 8) | 50][20];

il int cost(int i, int j) {
    if (!i) return 0;
    else return a[i] ^ a[j];
}

il void tomin(int &a, int b) {
    a = min(a, b);
    return;
}

void solve() {
    read(n);
    FOR(i, 1, n) read(a[i]), read(b[i]);
    memset(f, 0x3f, sizeof f);
    f[1][0][7] = 0;
    FOR(i, 1, n) {
        FOR(S, 0, (1 << 8) - 1) {
            FOR(k, -8, 7) {
                if (i + k < 0 || i + k > n) continue;
                if (f[i][S][8 + k] >= INF) continue;
                int lim = INF;
                if (S & 1) tomin(f[i + 1][S >> 1][7 + k], f[i][S][8 + k]);
                else FOR(j, 0, 7) {
                    if (i + j > n || i + j > lim) break;
                    if (S & (1 << j)) continue;
                    lim = min(lim, i + j + b[i + j]);
                    tomin(f[i][S | (1 << j)][8 + j], f[i][S][8 + k] + cost(i + k, i + j));
                }
            }
        }
    }
    int ans = INF;
    FOR(k, -8, 7) tomin(ans, f[n + 1][0][8 + k]);
    print(ans, '\n');
    return;
}

int main() {
    int T; read(T);
    while (T--) solve();
    return output(), 0;
}
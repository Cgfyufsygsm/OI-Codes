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

const int maxn = 3e5 + 5;
int n, a[maxn], cnt[maxn], vis[maxn], ans[10], tot;

int main() {
    int T; read(T);
    while (T--) {
        int n, m; read(n), read(m);
        FOR(i, 0, n - 1) cnt[i] = 0;
        FOR(i, 0, n - 1) {
            read(a[i]), --a[i];
            ++cnt[(i - a[i] + n) % n];
        }
        tot = 0;
        FOR(k, 0, n - 1) {
            if (cnt[k] < n - 2 * m) continue;
            FOR(i, 0, n - 1) vis[i] = 0;
            int circ = 0;
            FOR(i, 0, n - 1) {
                if (vis[i]) continue;
                int p = i;
                while (!vis[p]) {
                    vis[p] = 1;
                    p = (a[p] + k) % n;
                }
                ++circ;
            }
            if (n - circ <= m) ans[++tot] = k;
        }
        print(tot, ' ');
        FOR(i, 1, tot) print(ans[i], ' ');
        putchar('\n');
    }
    return output(), 0;
}
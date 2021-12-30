#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

int f[55][55][55][55];
char s[55][55];
int n;

int dfs(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (f[x1][y1][x2][y2] <= n) return f[x1][y1][x2][y2];
    f[x1][y1][x2][y2] = max(x2 - x1 + 1, y2 - y1 + 1);
    FOR(i, x1, x2) {
        bool ok = 1;
        FOR(j, y1, y2) if (s[i][j] == '#') {
            ok = 0;
            break;
        }
        if (ok) chkmin(f[x1][y1][x2][y2], dfs(x1, y1, i - 1, y2) + dfs(i + 1, y1, x2, y2));
    }
    FOR(j, y1, y2) {
        bool ok = 1;
        FOR(i, x1, x2) if (s[i][j] == '#') {
            ok = 0;
            break;
        }
        if (ok) chkmin(f[x1][y1][x2][y2], dfs(x1, y1, x2, j - 1) + dfs(x1, j + 1, x2, y2));
    }
    return f[x1][y1][x2][y2];
}

int main() {
    read(n);
    FOR(i, 1, n) read(s[i] + 1);
    FOR(l, 1, n) FOR(r, l, n) FOR(u, 1, n) FOR(d, u, n) f[l][u][r][d] = 1e9;
    print(dfs(1, 1, n, n));
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
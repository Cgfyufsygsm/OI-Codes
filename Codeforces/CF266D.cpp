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
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 205;
int n, m, dis[maxn][maxn], rk[maxn][maxn], ans = 2e9;

struct Edge {
    int u, v, w;
} e[maxn * maxn / 2];

int main() {
    read(n, m);
    FOR(i, 1, n) FOR(j, 1, n) dis[i][j] = 0x3f3f3f3f;
    FOR(i, 1, n) dis[i][i] = 0;
    FOR(i, 1, m) read(e[i].u, e[i].v, e[i].w), chkmin(dis[e[i].u][e[i].v], e[i].w), chkmin(dis[e[i].v][e[i].u], e[i].w);

    FOR(k, 1, n) FOR(i, 1, n) if (i != k) FOR(j, 1, n) if (i != j) chkmin(dis[i][j], dis[i][k] + dis[k][j]);
    FOR(u, 1, n) {
        FOR(j, 1, n) rk[u][j] = j;
        sort(rk[u] + 1, rk[u] + n + 1, [u](const int &a, const int &b) {return dis[u][a] < dis[u][b];});
        chkmin(ans, dis[u][rk[u][n]] << 1);
    }
    FOR(i, 1, m) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int pos = n;
        DEC(j, n - 1, 1) {
            if (dis[v][rk[u][j]] > dis[v][rk[u][pos]]) {
                chkmin(ans, dis[u][rk[u][j]] + dis[v][rk[u][pos]] + w);
                pos = j;
            }
        }
    }
    printf("%.2lf\n", ans / 2.0);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
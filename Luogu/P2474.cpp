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

const int maxn = 55;
int n, A, B, f[maxn][maxn], g[maxn][maxn];
char str[maxn][maxn];

void Floyd(int (&dis)[maxn][maxn], decltype(chkmax<int>) func) {
    FOR(k, 1, n) FOR(i, 1, n) FOR(j, 1, n) if (i != k && k != j && i != j) func(dis[i][j], dis[i][k] + dis[k][j]);
    return;
}

template<class Fun> void solve(Fun func) {
    int ans = 0;
    FOR(c, 1, n) if (A != c && B != c) FOR(d, 1, c - 1) if (A != d && B != d)
        ans += func(A, B, c, d);
    print(ans, ' ');
    return;
}

int main() {
    read(n, A, B);
    FOR(i, 1, n) read(str[i] + 1);
    FOR(i, 1, n) FOR(j, 1, i) {
        if (str[i][j] == '+' || str[j][i] == '-')
            f[i][j] = 2, g[i][j] = 1, f[j][i] = -1, g[j][i] = -2;
        else if (str[i][j] == '-' || str[j][i] == '+')
            f[i][j] = -1, g[i][j] = -2, f[j][i] = 2, g[j][i] = 1;
        else if (str[i][j] == '=' || str[j][i] == '=')
            f[i][j] = g[i][j] = f[j][i] = g[j][i] = 0;
        else f[i][j] = f[j][i] = 2, g[i][j] = g[j][i] = -2;
    }
    Floyd(f, chkmin<int>), Floyd(g, chkmax<int>);
    solve([](const int &a, const int &b, const int &c, const int &d) -> bool {
        return g[a][c] > f[d][b] || g[a][d] > f[c][b];
    });
    solve([](const int &a, const int &b, const int &c, const int &d) -> bool {
        return (f[a][c] == g[a][c] && f[d][b] == g[d][b] && f[a][c] == g[d][b]) ||
                (f[a][d] == g[a][d] && f[c][b] == g[c][b] && f[a][d] == g[c][b]);
    });
    solve([](const int &a, const int &b, const int &c, const int &d) -> bool {
        return f[a][c] < g[d][b] || f[a][d] < g[c][b];
    });
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
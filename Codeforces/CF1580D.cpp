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

using ll = long long;
const int maxn = 4005;
int n, m, ls[maxn], rs[maxn], stk[maxn], top;
ll a[maxn], size[maxn], f[maxn][maxn], w[maxn];

void dfs(int u) {
    size[u] = 1;
    if (ls[u]) {
        dfs(ls[u]), w[ls[u]] = a[ls[u]] - a[u];
        DEC(i, size[u], 0)
            DEC(j, size[ls[u]], 0)
                chkmax(f[u][i + j], f[u][i] + f[ls[u]][j] + j * (m - j) * w[ls[u]]);
        size[u] += size[ls[u]];
    }
    if (rs[u]) {
        dfs(rs[u]), w[rs[u]] = a[rs[u]] - a[u];
        DEC(i, size[u], 0)
            DEC(j, size[rs[u]], 0)
                chkmax(f[u][i + j], f[u][i] + f[rs[u]][j] + j * (m - j) * w[rs[u]]);
        size[u] += size[rs[u]];
    }
    return;
}

int main() {
    read(n, m);
    FOR(i, 1, n) read(a[i]);
    stk[top = 1] = 1;
    FOR(i, 2, n) {
        while (top && a[stk[top]] > a[i]) --top;
        if (!top) ls[i] = stk[top + 1];
        else ls[i] = rs[stk[top]], rs[stk[top]] = i;
        stk[++top] = i;
    }
    dfs(stk[1]);
    print(f[stk[1]][m]);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
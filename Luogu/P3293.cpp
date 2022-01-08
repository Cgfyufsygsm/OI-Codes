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

const int maxn = 2e5 + 5, N = 1e5;
struct node {
    int ch[2], sum;
} t[maxn * 50];
int root[maxn], tot, n, m;

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

int clone(int u) {
    t[++tot] = t[u];
    return tot;
}

int build(int u, int i, int j) {
    u = ++tot;
    if (i == j) return u;
    ls(u) = build(ls(u), i, M);
    rs(u) = build(rs(u), M + 1, j);
    return u;
}

int insert(int u, int i, int j, int x) {
    u = clone(u);
    ++t[u].sum;
    if (i == j) return u;
    if (x <= M) ls(u) = insert(ls(u), i, M, x);
    else rs(u) = insert(rs(u), M + 1, j, x);
    return u;
}

int query(int u1, int u2, int i, int j, int x, int y) {
    if (x <= i && y >= j) return t[u2].sum - t[u1].sum;
    int ret = 0;
    if (x <= M) ret += query(ls(u1), ls(u2), i, M, x, y);
    if (y > M) ret += query(rs(u1), rs(u2), M + 1, j, x, y);
    return ret;
}

int main() {
    read(n, m);
    root[0] = build(root[0], 1, n);
    FOR(i, 1, n) {
        int x; read(x);
        root[i] = insert(root[i - 1], 0, N, x);
    }
    while (m--) {
        int b, x, l, r; read(b, x, l, r);
        int ans = 0;
        DEC(k, 17, 0) {
            if ((((b >> k) & 1) && !query(root[l - 1], root[r], 0, N, max(ans - x, 0), min(ans + (1 << k) - 1 - x, N)))
                || ((!((b >> k) & 1)) && (query(root[l - 1], root[r], 0, N, max(ans + (1 << k) - x, 0), min(ans + (1 << (k + 1)) - 1 - x, N)))))
                ans += (1 << k);
        }
        print(ans ^ b);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
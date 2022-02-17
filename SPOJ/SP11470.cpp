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
const int maxn = 1e5 + 5;
int a[maxn], root[maxn], n, m, tot;
struct node {
    ll sum, add;
    int ch[2];
} t[maxn * 50];

int clone(int u) {
    t[++tot] = t[u];
    return tot;
}

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

il void pushup(int u) {t[u].sum = t[ls(u)].sum + t[rs(u)].sum;}

int build(int u, int i, int j) {
    if (!u) u = ++tot;
    if (i == j) {
        read(t[u].sum);
        return u;
    }
    ls(u) = build(ls(u), i, M);
    rs(u) = build(rs(u), M + 1, j);
    pushup(u);
    return u;
}

int modify(int u, int i, int j, int x, int y, ll d) {
    u = clone(u);
    t[u].sum += d * (min(j, y) - max(i, x) + 1);
    if (x <= i && y >= j) {
        t[u].add += d;
        //printf("addedd %d %d %d\n", t[u].add, i, j);
        return u;
    }
    if (x <= M) ls(u) = modify(ls(u), i, M, x, y, d);
    if (y > M) rs(u) = modify(rs(u), M + 1, j, x, y, d);
    return u;
}

ll query(int u, int i, int j, int x, int y, ll tag) {
    //printf("%d %d %d %d %d\n", u, i, j, x, y);
    //printf("%d %d %lld\n", i, j, t[u].add);
    if (x <= i && y >= j) return t[u].sum + tag * (min(j, y) - max(i, x) + 1);;
    ll ret = 0;
    if (x <= M) ret += query(ls(u), i, M, x, y, tag + t[u].add);
    if (y > M) ret += query(rs(u), M + 1, j, x, y, tag + t[u].add);
    return ret;
}

int main() {
    read(n, m);
    root[0] = build(root[0], 1, n);
    int t = 0, b = 0;
    FOR(i, 1, m) {
        char s[2]; read(s);
        if (s[0] == 'C') {
            int l, r; ll d; read(l, r, d);
            root[++t] = modify(root[t], 1, n, l, r, d);
        } else if (s[0] == 'Q') {
            int l, r; read(l, r);
            print(query(root[t], 1, n, l, r, 0));
        } else if (s[0] == 'H') {
            int l, r, tt; read(l, r, tt);
            print(query(root[tt], 1, n, l, r, 0));
        } else read(t);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
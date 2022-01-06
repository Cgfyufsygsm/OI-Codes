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

const int maxn = 6e5 + 5;
int n, m, tot, root[maxn];
int s[maxn];

struct node {
    int ch[2], latest;
    node() {ch[0] = ch[1] = 0, latest = -1;}
} t[maxn * 25];

int clone(int u) {
    t[++tot] = t[u];
    return tot;
}

int insert(int u, int id, int k, int val) {
    u = clone(u);
    if (k < 0) return t[u].latest = id, u;
    int c = (val >> k) & 1;
    t[u].ch[c] = insert(t[u].ch[c], id, k - 1, val);
    t[u].latest = max(t[t[u].ch[0]].latest, t[t[u].ch[1]].latest);
    return u;
}

int query(int u, int val, int k, int l) {
    if (k < 0) return s[t[u].latest] ^ val;
    int c = (val >> k) & 1;
    if (t[t[u].ch[c ^ 1]].latest >= l) return query(t[u].ch[c ^ 1], val, k - 1, l);
    else return query(t[u].ch[c], val, k - 1, l);
}

int main() {
    read(n, m);
    root[0] = insert(0, 0, 23, 0);
    FOR(i, 1, n) {
        read(s[i]), s[i] ^= s[i - 1];
        root[i] = insert(root[i - 1], i, 23, s[i]);
    }
    while (m--) {
        char str[2]; read(str);
        if (str[0] == 'A') {
            ++n, read(s[n]), s[n] ^= s[n - 1];
            root[n] = insert(root[n - 1], n, 23, s[n]);
        } else {
            int l, r, x; read(l, r, x);
            print(query(root[r - 1], s[n] ^ x, 23, l - 1));
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
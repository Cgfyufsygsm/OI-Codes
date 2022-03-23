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

const int maxn = 2e4 + 5;
int n, head[maxn], cnte;

struct Edge {
    int to, nxt, w;
} e[maxn << 1];

il void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].nxt = head[u];
    e[cnte].w = w;
    head[u] = cnte;
    return;
}

int maxp[maxn], root, tot, size[maxn], vis[maxn];

void getRt(int u, int fa) {
    size[u] = 1, maxp[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == fa || vis[v]) continue;
        getRt(v, u);
        size[u] += size[v];
        chkmax(maxp[u], size[v]);
    }
    chkmax(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

int dis[maxn], buc[3], tmp[3], ans[3];

void getDis(int u, int fa) {
    ++tmp[dis[u]];
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == fa || vis[v]) continue;
        dis[v] = (dis[u] + e[i].w) % 3;
        getDis(v, u);
    }
    return;
}

void calc(int u) {
    buc[0] = 1, buc[1] = buc[2] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (vis[v]) continue;
        dis[v] = e[i].w;
        tmp[0] = tmp[1] = tmp[2] = 0;
        getDis(v, u);
        FOR(a, 0, 2) FOR(b, 0, 2) ans[(a + b) % 3] += buc[a] * tmp[b];
        FOR(a, 0, 2) buc[a] += tmp[a];
    }
    return;
}

void divide(int u) {
    vis[u] = 1;
    calc(u);
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (vis[v]) continue;
        maxp[root = 0] = n, tot = size[v];
        getRt(v, u);
        getRt(root, 0);
        divide(root);
    }
    return;
}

int main() {
    read(n);
    FOR(i, 2, n) {
        int u, v, w; read(u, v, w), w %= 3;
        add(u, v, w), add(v, u, w);
    }
    maxp[root = 0] = tot = n;
    getRt(1, 0);
    getRt(root, 0);
    divide(root);
    int up = ((ans[0] << 1) + n), down = ((ans[1] + ans[2]) << 1) + up, g = __gcd(up, down);
    up /= g, down /= g;
    printf("%d/%d\n", up, down);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
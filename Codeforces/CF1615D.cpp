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

const int maxn = 2e5 + 5;
int r[maxn], vis[maxn], n, m, flag;
struct edge {
    int to, w;
    edge(int v, int d) : to(v), w(d) {}
};
vector<edge> G[maxn], G1[maxn];

il int parity(int n) {return __builtin_popcount(n) & 1;}

void dfs1(int u, int val) {
    vis[u] = 1, r[u] = val;
    for (auto &e : G1[u]) {
        int v = e.to, w = e.w;
        if (vis[v] && (w ^ val) != r[v]) flag = 1;
        if (!vis[v]) dfs1(v, val ^ w);
    }
    return;
}

void dfs2(int u, int fa) {
    for (auto &e : G[u]) {
        int v = e.to, w = e.w;
        if (v == fa) continue;
        print(v, u, w == -1 ? r[u] ^ r[v] : w);
        dfs2(v, u);
    }
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n, m);
        flag = 0;
        FOR(i, 1, n) r[i] = vis[i] = 0, G[i].clear(), G1[i].clear();
        FOR(i, 1, n - 1) {
            int a, b, c; read(a, b, c);
            G[a].push_back(edge(b, c));
            G[b].push_back(edge(a, c));
            if (c == -1) continue;
            G1[a].push_back(edge(b, parity(c)));
            G1[b].push_back(edge(a, parity(c)));
        }
        FOR(i, 1, m) {
            int a, b, c; read(a, b, c);
            G1[a].push_back(edge(b, c));
            G1[b].push_back(edge(a, c));
        }
        FOR(i, 1, n) if (!vis[i]) dfs1(i, 0);
        if (flag) print("NO");
        else {
            print("YES");
            dfs2(1, 0);
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
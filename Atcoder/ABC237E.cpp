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
const int maxn = 2e5 + 5;
struct edge {
    int to; ll w;
    edge(int v = 0, ll dis = 0) : to(v), w(dis) {}
};
vector<edge> G[maxn];
int h[maxn], n, m, inq[maxn];
ll dis[maxn];

int main() {
    read(n, m);
    FOR(i, 1, n) read(h[i]), dis[i] = -2e18;
    FOR(i, 1, m) {
        int u, v; read(u, v);
        G[u].push_back(edge(v, h[u] - h[v] > 0 ? h[u] - h[v] : 2 * (h[u] - h[v])));
        G[v].push_back(edge(u, h[v] - h[u] > 0 ? h[v] - h[u] : 2 * (h[v] - h[u])));
    }
    queue<int> q;
    q.push(1), dis[1] = 0, inq[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        inq[u] = 0, q.pop();
        for (auto &p : G[u]) {
            int v = p.to;
            if (dis[u] + p.w > dis[v]) {
                dis[v] = dis[u] + p.w;
                if (!inq[v]) inq[v] = 1, q.push(v);
            }
        }
    }
    ll ans = -4e18;
    FOR(i, 1, n) chkmax(ans, dis[i]);
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
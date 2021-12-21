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
    while (!isspace(c)) s[p++] = c, c = getchar();
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
using ll = long long;
int n, m, a[maxn], b[maxn], val[maxn * 2];
int head[maxn * 3], cnt;

struct edge {
    int to, nxt;
    ll w;
} e[maxn * 7];

il void add(int u, int v, ll w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    return;
}

ll dijkstra(int s, int t) {
    static ll dis[maxn * 3];
    static bool vis[maxn * 3];
    using pli = pair<ll, int>;
    priority_queue<pli, vector<pli>, greater<pli> > q;
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0, q.push(pli(0, s));
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (!vis[u]) {
            vis[u] = 1;
            for (int i = head[u]; i; i = e[i].nxt) {
                int v = e[i].to;
                if (dis[u] + e[i].w < dis[v]) {
                    dis[v] = dis[u] + e[i].w;
                    q.push(pli(dis[v], v));
                }
            }
        }
    }
    return dis[t];
}

int main() {
    read(n, m);
    FOR(i, 1, n) read(a[i]), val[i] = m - a[i];
    FOR(i, 1, n) read(b[i]), val[i + n] = b[i];
    sort(val + 1, val + 2 * n + 1);
    int tot = unique(val + 1, val + 2 * n + 1) - val - 1;
    FOR(i, 1, tot - 1) add(n + i, n + i + 1, val[i + 1] - val[i]);
    add(n + tot, n + 1, (val[1] - val[tot] + m) % m);
    FOR(i, 1, n) add(i, n + lower_bound(val + 1, val + tot + 1, m - a[i]) - val, 0);
    FOR(i, 1, n) add(n + lower_bound(val + 1, val + tot + 1, b[i]) - val, i, 0);
    print(dijkstra(1, n));
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
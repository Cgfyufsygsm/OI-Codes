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

const int maxn = 3e3 + 5, maxm = 1e4 + 5;

using ll = long long;
int head[maxn], cnte, n, m, cntq[maxn], inq[maxn], vis[maxn];
ll dis[maxn], h[maxn];
struct edge {
    int to, nxt;
    ll w;
} e[maxm];

il void add(int u, int v, ll w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

bool SPFA(int s) {
    memset(h, 0x3f, sizeof h);
    h[s] = 0, cntq[s] = inq[s] = 1;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop(), inq[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (h[u] + e[i].w < h[v]) {
                h[v] = h[u] + e[i].w;
                if (!inq[v]) {
                    q.push(v), inq[v] = 1, ++cntq[v];
                    if (cntq[v] > n) return 0;
                }
            }
        }
    }
    return 1;
}

void Dijkstra(int s) {
    FOR(i, 1, n) dis[i] = 1e9, vis[i] = 0;
    dis[s] = 0;
    using pli = pair<ll, int>;
    priority_queue<pli, vector<pli>, greater<pli> > q;
    q.push(pli(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[u] + e[i].w < dis[v]) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) q.push(pli(dis[v], v));
            }
        }
    }
    return;
}

int main() {
    read(n, m);
    FOR(i, 1, m) {
        int u, v, w; read(u, v, w);
        add(u, v, w);
    }
    FOR(i, 1, n) add(0, i, 0);
    if (!SPFA(0)) print(-1);
    else {
        FOR(u, 1, n) for (int i = head[u]; i; i = e[i].nxt) e[i].w += h[u] - h[e[i].to];
        FOR(u, 1, n) {
            Dijkstra(u);
            ll ans = 0;
            FOR(i, 1, n) ans += dis[i] == 1e9 ? i * 1e9 : i * (dis[i] + h[i] - h[u]);
            print(ans);
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
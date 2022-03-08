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

const int maxn = 1005, maxm = 4005;
int head[maxn], to[maxm], nxt[maxm], w[maxm], cnte, dis[maxn], cnt[maxn], inq[maxn], n, m;

struct Edge {
    int u, v;
} e[maxm];

vector<int> G[maxn], rG[maxn];
bool vis1[maxn], vis2[maxn];

void dfs(int u, bool (&vis)[maxn], vector<int> (&G)[maxn]) {
    vis[u] = 1;
    for (int v : G[u]) {
        if (!vis[v]) dfs(v, vis, G);
    }
    return;
}

il void add(int u, int v, int w) {
    to[++cnte] = v;
    YangTY::w[cnte] = w;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

bool SPFA() {
    queue<int> q;
    memset(dis, 0x3f, sizeof dis);
    dis[0] = 0, inq[0] = cnt[0] = 1, q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop(), inq[u] = 0;
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            if (dis[v] > dis[u] + w[i]) {
                dis[v] = dis[u] + w[i];
                if (!inq[v]) {
                    if (++cnt[v] > n) return true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int main() {
    read(n, m);
    FOR(i, 1, m) {
        read(e[i].u, e[i].v);
        G[e[i].u].push_back(e[i].v), rG[e[i].v].push_back(e[i].u);
    }
    dfs(1, vis1, G), dfs(n, vis2, rG);
    if (!vis1[n]) return puts("-1"), 0;
    FOR(i, 1, m)
        if (vis1[e[i].u] && vis2[e[i].v]) add(e[i].v, e[i].u, -1), add(e[i].u, e[i].v, 9);
    FOR(i, 1, n) add(0, i, 0);
    if (SPFA()) return puts("-1"), 0;
    print(n, m);
    FOR(i, 1, m) print(e[i].u, e[i].v, (vis1[e[i].u] && vis2[e[i].v]) ? dis[e[i].v] - dis[e[i].u] : 8);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
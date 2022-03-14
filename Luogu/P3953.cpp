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

const int maxn = 1e5 + 5, maxm = 2e5 + 5, maxk = 52;
int T, n, m, K, mod;

struct Graph {
    int head[maxn], cnte;
    struct Edge {
        int to, nxt, w;
    } e[maxm];
    il void add(int u, int v, int w) {
        e[++cnte].to = v;
        e[cnte].nxt = head[u];
        e[cnte].w = w;
        head[u] = cnte;
        return;
    }
    void clear() {
        memset(head, 0, sizeof head);
        cnte = 0;
        return;
    }
} G[3];

int dis1[maxn], disn[maxn], f[maxn][maxk], p[maxn], ord[maxn];

void dijkstra(int s, Graph &G, int (&dis)[maxn]) {
    static bool vis[maxn];
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    memset(dis, 0x3f, sizeof dis), memset(vis, 0, sizeof vis);
    dis[s] = 0, q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = G.head[u]; i; i = G.e[i].nxt) {
            int &v = G.e[i].to, &w = G.e[i].w;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                if (!vis[v]) q.push({dis[v], v});
            }
        }
    }
    return;
}

void toposort(Graph &G, int (&ord)[maxn], bool &flg) {
    static int ind[maxn], q[maxn], qh, qt, cnt;
    memset(ind, 0, sizeof ind);
    for (int i = 1; i <= G.cnte; ++i)
        ++ind[G.e[i].to];
    qh = 1, qt = 0, cnt = 0;
    FOR(i, 1, n) if (!ind[i]) q[++qt] = i;
    while (qh <= qt) {
        int u = q[qh++]; ord[u] = ++cnt;
        for (int i = G.head[u]; i; i = G.e[i].nxt) {
            int &v = G.e[i].to;
            if (!--ind[v]) q[++qt] = v;
        }
    }
    FOR(i, 1, n) flg |= (ind[i] && dis1[i] + disn[i] <= dis1[n] + K);
    return;
}

int main() {
    read(T);
    while (T--) {
        read(n, m, K, mod);
        G[0].clear(), G[1].clear(), G[2].clear();
        FOR(i, 1, m) {
            int a, b, c; read(a, b, c);
            G[0].add(a, b, c), G[1].add(b, a, c);
            if (!c) G[2].add(a, b, c);
        }
        dijkstra(1, G[0], dis1);
        dijkstra(n, G[1], disn);
        bool flg = 0;
        toposort(G[2], ord, flg);
        if (flg) {
            print(-1);
            continue;
        }
        toposort(G[0], ord, flg);
        FOR(i, 1, n) p[i] = i;
        sort(p + 1, p + n + 1, [](const int &a, const int &b) {return dis1[a] == dis1[b] ? ord[a] < ord[b] : dis1[a] < dis1[b];});
        memset(f, 0, sizeof f);
        int ans = 0;
        f[1][0] = 1 % mod;
        FOR(j, 0, K) {
            FOR(uu, 1, n) {
                int &u = p[uu];
                for (int i = G[0].head[u]; i; i = G[0].e[i].nxt) {
                    int &v = G[0].e[i].to, &w = G[0].e[i].w;
                    if (j + w + dis1[u] - dis1[v] > K) continue;
                    int &fto = f[v][j + w + dis1[u] - dis1[v]];
                    fto = (fto + f[u][j]) % mod;
                }
            }
            ans = (ans + f[n][j]) % mod;
        }
        print(ans);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define il inline
#define popcount(x) __builtin_popcount(x)

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
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int maxn = 3005, maxm = 9e6 + 5;

const int INF = 1e9;

struct edge {
    int to, nxt, w;
} e[maxm << 1];

int head[maxn], dep[maxn], cur[maxn], cnt = 1;
int s, t;

il void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].w = 0;
    e[cnt].nxt = head[v];
    head[v] = cnt;
    return;
}

bool bfs() {
    static int q[maxn], qhead, qtail;
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof head);
    q[qhead = qtail = 1] = s;
    dep[s] = 0;
    while (qhead <= qtail) {
        int u = q[qhead++];
        GO(u, head) {
            if (e[i].w > 0 && dep[v] == -1) {
                q[++qtail] = v;
                dep[v] = dep[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int in) {
    if (u == t) return in;
    int out = 0;
    GO(u, cur) {
        cur[u] = i;
        if (e[i].w > 0 && dep[v] == dep[u] + 1) {
            int res = dfs(v, min(in, e[i].w));
            e[i].w -= res, e[i ^ 1].w += res;
            in -= res, out += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}

int ans;

void dinic(int val) {
    int ret = val;
    while (bfs()) {
        ret -= dfs(s, INF);
        if (ret <= ans) return;
    }
    ans = ret;
    return;
}

int A, B, m;
int a[205], b[3005], st[2][3005], top[2], tot, U[maxm], V[maxm], vis[3005];
std::vector<int> G[205];

void connect() {
    memset(head, 0, sizeof head), cnt = 1;
    FOR(i, 1, tot) if (vis[U[i]] && vis[V[i]]) add(U[i], V[i], 1);
    FOR(i, 1, top[0]) if (vis[st[0][i]]) add(s, st[0][i], 1);
    FOR(i, 1, top[1]) if (vis[st[1][i]]) add(st[1][i], t, 1);
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(A), read(B), read(m);
        FOR(i, 1, A) read(a[i]);
        FOR(i, 1, B) read(b[i]), st[b[i] & 1][++top[b[i] & 1]] = i;
        s = B + 1, t = B + 2, ans = 0;
        FOR(i, 1, top[0]) {
            FOR(j, 1, top[1]) {
                if (!(popcount(st[0][i] | st[1][j]) & 1)) {
                    U[++tot] = st[0][i];
                    V[tot] = st[1][j];
                }
            }
        }
        memset(head, 0, sizeof head), cnt = 1;
        FOR(i, 1, tot) add(U[i], V[i], 1);
        FOR(i, 1, top[0]) add(s, st[0][i], 1);
        FOR(i, 1, top[1]) add(st[1][i], t, 1);
        dinic(B);
        FOR(i, 1, m) {
            int x, y; read(x), read(y);
            G[x].push_back(y);
        }
        FOR(x, 1, A) {
            memset(vis, 0, sizeof vis);
            for (auto v : G[x]) ++vis[v];
            int P = 1;
            FOR(i, 1, B) P += vis[i];
            if (P <= ans) continue;
            connect(), dinic(P);
        }
        FOR(x, 1, A) {
            FOR(y, 1, A) {
                memset(vis, 0, sizeof vis);
                if (!((a[x] ^ a[y]) & 1)) continue;
                for (auto v : G[x]) ++vis[v];
                for (auto v : G[y]) ++vis[v];
                int P = 2;
                FOR(i, 1, B) {
                    vis[i] = (vis[i] < 2) ? 0 : 1;
                    P += vis[i];
                }
                if (P <= ans) continue;
                connect(), dinic(P);
            }
        }
        print(ans), putchar('\n');
    }
    return output(), 0;
}
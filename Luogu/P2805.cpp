#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define il inline

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

const int maxn = 1200, maxm = 1e6 + 5;

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

int dinic() {
    int ret = 0;
    while (bfs()) ret += dfs(s, INF);
    return ret;
}

int n, m, val[maxn], ind[maxn], vis[maxn];
std::vector<int> e0[maxn];

il int encode(int x, int y) {return (x - 1) * m + y;}

void topo() {
    static int q[maxn], head, tail;
    FOR(u, 1, n * m) if (!ind[u]) q[++tail] = u, vis[u] = 1;
    while (head <= tail) {
        int u = q[head++];
        for (auto v : e0[u])
            if (!vis[v] && !--ind[v])
                q[++tail] = v, vis[v] = 1;
    }
    return;
}

int main() {
    read(n), read(m);
    s = n * m + 1, t = s + 1;
    int tot = 0, sum = 0;
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            ++tot;
            int w;
            read(val[tot]), read(w);
            while (w--) {
                int tr, tc;
                read(tr), read(tc);
                e0[tot].push_back(encode(++tr, ++tc));
                ++ind[encode(tr, tc)];
            }
            if (j < m) e0[tot + 1].push_back(tot), ++ind[tot];
        }
    }
    topo();
    FOR(u, 1, n * m) {
        if (!vis[u]) continue;
        for (auto v : e0[u]) {
            if (!vis[v]) continue;
            add(v, u, INF);
        }
        if (val[u] >= 0) add(s, u, val[u]), sum += val[u];
        else add(u, t, -val[u]);
    }
    print(sum - dinic());
    return output(), 0;
}
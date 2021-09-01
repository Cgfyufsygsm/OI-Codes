#include <cstdio>
#include <cctype>
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

const int maxn = 4085, maxm = 1e5 + 5;

typedef long long ll;
const ll INF = 1e18;

struct edge {
    int from, to, nxt;
    ll w;
} e[maxm << 1];

int head[maxn], dep[maxn], cur[maxn], cnt = 1;
int n, m, s, t;

il void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].from = u;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].from = v;
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

ll dfs(int u, ll in) {
    if (u == t) return in;
    ll out = 0;
    GO(u, cur) {
        cur[u] = i;
        if (e[i].w > 0 && dep[v] == dep[u] + 1) {
            ll res = dfs(v, min(in, e[i].w));
            e[i].w -= res, e[i ^ 1].w += res;
            in -= res, out += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}

ll dinic() {
    ll ret = 0;
    while (bfs()) ret += dfs(s, INF);
    return ret;
}

int dfn[maxn], low[maxn], ins[maxn], stk[maxn], top;
int dfnClock, scc[maxn], sccCnt;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u, ins[u] = 1;
    GO(u, head) {
        if (!e[i].w) continue;
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        while (true) {
            int now = stk[top--];
            ins[now] = 0;
            scc[now] = sccCnt;
            if (now == u) break;
        }
    }
    return;
}

int main() {
    read(n), read(m), read(s), read(t);
    FOR(i, 1, m) {
        int u, v; ll w; read(u), read(v), read(w);
        add(u, v, w);
    }
    dinic();
    FOR(i, 1, n) if (!scc[i]) tarjan(i);
    for (int i = 2; i < cnt; i += 2) {
        int u = e[i].from, v = e[i].to;
        if (!e[i].w && scc[u] != scc[v]) {
            print(1), putchar(' ');
            if (scc[s] == scc[u] && scc[v] == scc[t]) print(1);
            else print(0);
            putchar('\n');
        } else print(0), putchar(' '), print(0), putchar('\n'); 
    }
    return output(), 0;
}
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
}// namespace fastIO

using namespace fastIO;

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int maxn = 105, maxm = 1005;

using ll = long long;
using db = double;
const ll INF = 1e18;

struct edge {
    int to, nxt;
    db w;
} e[maxm << 1];

int head[maxn], dep[maxn], cur[maxn], cnt = 1;
int s, t;

il void add(int u, int v, db w) {
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
            if (e[i].w > 1e-7 && dep[v] == -1) {
                q[++qtail] = v;
                dep[v] = dep[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}

db dfs(int u, db in) {
    if (u == t) return in;
    db out = 0;
    GO(u, cur) {
        cur[u] = i;
        if (e[i].w > 0 && dep[v] == dep[u] + 1) {
            db res = dfs(v, min(in, e[i].w));
            e[i].w -= res, e[i ^ 1].w += res;
            in -= res, out += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}

db dinic() {
    db ret = 0;
    while (bfs()) ret += dfs(s, INF);
    return ret;
}

int n, m, P;

struct E {
    int u, v, w;
} e0[maxm];

void build(db mid = INF) {
    cnt = 1, s = 1, t = n;
    memset(head, 0, sizeof head);
    FOR(i, 1, m) add(e0[i].u, e0[i].v, min((db)e0[i].w, mid));
    return;
}

template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}

int main() {
    read(n), read(m), read(P);
    FOR(i, 1, m) read(e0[i].u), read(e0[i].v), read(e0[i].w);
    build();
    int flow = (int)dinic();
    printf("%d\n", flow);
    db l = 0, r = flow + 1e-5, ans;
    while (r - l > 1e-7) {
        db mid = (l + r) / 2;
        build(mid);
        if (myabs(dinic() - (db)flow) <= 1e-6) ans = mid, r = mid;
        else l = mid;
    }
    printf("%.4lf\n", ans * P);
    return 0;
}

#include <vector>

std::vector<int> v;

int main() {
    int T;
    while (T--) {
        std::vector<int> v0;
        v.swap(v0);
    }
}
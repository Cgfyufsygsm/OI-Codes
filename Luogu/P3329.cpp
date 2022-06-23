#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define szof(a) ((int) (a).size())
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fileIn(s) freopen(s, "r", stdin)
#define fileOut(s) freopen(s, "w", stdout)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))

using namespace std;

namespace YangTY {

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

const int maxn = 155, maxm = 2e4 + 5;
int dis[maxn][maxn], n, m;
int head[maxn], cnte = 1;

struct Edge {
    int to, nxt, w;
} e[maxm];

il void add(int u, int v, int w) {
    e[++cnte] = {v, head[u], w}, head[u] = cnte;
    e[++cnte] = {u, head[v], 0}, head[v] = cnte;
    return;
}

int node[maxn], dep[maxn], cur[maxn], S, T;
int tmp1[maxn], tmp2[maxn];

void init() {
    for (int i = 2; i <= cnte; i += 2)
        e[i].w += e[i ^ 1].w, e[i ^ 1].w = 0;
    return;
}

bool bfs() {
    // debug("another rund");
    static int q[maxn], qh, qt;
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof cur);
    q[qh = qt = 1] = S, dep[S] = 0;
    while (qh <= qt) {
        int u = q[qh++];
        for (int i = head[u]; i; i = e[i].nxt) {
            int &v = e[i].to, &w = e[i].w;
            if (w > 0 && dep[v] == -1) {
                q[++qt] = v;
                dep[v] = dep[u] + 1;
                if (v == T) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int in) {
    if (u == T) return in;
    int out = 0;
    for (int i = cur[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        cur[u] = i;
        if (e[i].w > 0 && dep[v] == dep[u] + 1) {
            int res = dfs(v, min(in, e[i].w));
            in -= res, out += res;
            e[i].w -= res, e[i ^ 1].w += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}


int dinic() {
    int res = 0;
    init();
    while (bfs()) res += dfs(S, 1e9);
    return res;
}

void divide(int l, int r) {
    if (l == r) return;
    S = node[l], T = node[l + 1];
    dis[S][T] = dis[T][S] = dinic();
    int cnt1 = 0, cnt2 = 0, s = S, t = T;
    FOR(i, l, r) {
        if (~dep[node[i]]) tmp1[++cnt1] = node[i];
        else tmp2[++cnt2] = node[i];
    }
    FOR(i, 1, cnt1) node[l + i - 1] = tmp1[i];
    FOR(i, 1, cnt2) node[l + cnt1 + i - 1] = tmp2[i];
    divide(l, l + cnt1 - 1), divide(l + cnt1, r);
    FOR(i, 1, cnt1) FOR(j, 1, cnt2) {
        int ii = node[l + i - 1], jj = node[l + cnt1 + j - 1];
        dis[ii][jj] = dis[jj][ii] = min(dis[ii][s], dis[s][t], dis[jj][t]);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        memset(head, 0, sizeof head), cnte = 1;
        memset(dis, 0x3f, sizeof dis);
        FOR(i, 1, m) {
            int u, v, w; cin >> u >> v >> w;
            add(u, v, w), add(v, u, w);
        }
        FOR(i, 1, n) node[i] = i;
        divide(1, n);
        int q; cin >> q;
        while (q--) {
            int x; cin >> x;
            int ans = 0;
            FOR(i, 1, n) FOR(j, i + 1, n) ans += (dis[i][j] <= x);
            cout << ans << '\n';
        }
        cout << '\n';
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
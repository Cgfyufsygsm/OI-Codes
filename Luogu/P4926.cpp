#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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

using db = double;
const int maxn = 1005;

int head[maxn], head0[maxn], cnte, cnte0, n, m;
int inq[maxn], vis[maxn];
db dis[maxn];
struct Edge {
    int to, nxt;
    db w;
} e[maxn * 3];

struct Constraint {
    int o, a, b, k;
} a[maxn];

il void add(int u, int v, db w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

void buildEdge(db T) {
    cnte = cnte0;
    memcpy(head, head0, sizeof head);
    FOR(i, 1, m) {
        if (a[i].o == 1) add(a[i].b, a[i].a, log2(a[i].k - T));
        else add(a[i].b, a[i].a, -log2(a[i].k + T));
    }
    return;
}

bool SPFA() {
    memset(vis, 0, sizeof vis), memset(dis, 0xc2, sizeof dis), memset(inq, 0, sizeof inq);
    queue<int> q; vis[n + 1] = inq[n + 1] = 1, dis[n + 1] = 0, q.push(n + 1);
    while (!q.empty()) {
        int u = q.front(); inq[u] = 0, q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int &v = e[i].to;
            if (dis[u] + e[i].w > dis[v]) {
                dis[v] = dis[u] + e[i].w;
                if (!inq[v]) {
                    if (++vis[v] > n) return true;
                    q.push(v), inq[v] = 1;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> n >> m >> t;
    db l = 0, r = 1e12;
    FOR(i, 1, m) {
        cin >> a[i].o >> a[i].a >> a[i].b >> a[i].k;
        if (a[i].o == 1) chkmin(r, (db)a[i].k);
    }
    FOR(i, 1, t) {
        int c, x; cin >> c >> x;
        add(0, c, log2(x)), add(c, 0, -log2(x));
    }
    FOR(i, 0, n) add(n + 1, i, 0);
    cnte0 = cnte;
    memcpy(head0, head, sizeof head);
    buildEdge(0);
    if (!SPFA()) {
        cout << -1 << endl;
        return 0;
    }
    while (r - l > 1e-6) {
        db mid = (l + r) / 2.0;
        buildEdge(mid);
        if (SPFA()) l = mid;
        else r = mid;
    }
    cout << fixed << setprecision(9) << l << endl;
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
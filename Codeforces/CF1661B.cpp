#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

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

const int maxn = 1 << 15 | 5;

int n, m, s, head[maxn], vis[maxn];
int dis[maxn];

struct edge {
    int to, nxt;
    int w;
} e[maxn << 2];
int cnte;

il void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].nxt = head[u];
    e[cnte].w = w;
    head[u] = cnte;
    return;
}

void dijkstra() {
    using pli = pair<int, int>;
    std::priority_queue<pli, vector<pli>, greater<pli> > q;
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0; q.push(pli(0, s));
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (!vis[u]) {
            vis[u] = 1;
            for (int i = head[u]; i; i = e[i].nxt) {
                int &v = e[i].to; int &w = e[i].w;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    q.push(pli(dis[v], v));
                }
            }
        }
    }
    return;
}

int main() {
    FOR(from, 1, 32767) {
        int to = (from + 1) % 32768;
        add(to, from, 1);
        to = (from * 2) % 32768;
        add(to, from, 1);
    }
    s = 0;
    dijkstra();
    int n; cin >> n;
    FOR(i, 1, n) {
        int x; cin >> x;
        cout << dis[x] << ' ';
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
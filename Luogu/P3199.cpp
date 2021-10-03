#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

typedef double db;
typedef long long ll;
const db EPS = 1e-11;
const int maxn = 3005, maxm = 10000 + 5;

struct edge {
    int to, nxt;
    db w;
} e[maxm];
int n, m, head[maxn], cnte;

db dis[maxn];
int vis[maxn], cnt[maxn];

il void add(int u, int v, db w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

bool SPFA(int u, db mid) {
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        db w = e[i].w - mid;
        if (dis[u] + w < dis[v]) {
            dis[v] = dis[u] + w;
            if (vis[v] || SPFA(v, mid)) return true;
        }
    }
    vis[u] = 0;
    return false;
}

bool check(db mid) {
    memset(vis, 0, sizeof vis);
    memset(dis, 0, sizeof dis);
    bool ret = 0;
    FOR(i, 1, n) dis[i] = 0, ret |= SPFA(i, mid);
    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    FOR(i, 1, m) {
        int u, v; db w;
        scanf("%d %d %lf", &u, &v, &w);
        add(u, v, w);
    }
    db l = -1e7, r = 1e7;
    while (r - l > EPS) {
        db mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    printf("%.8lf\n", l);
    return 0;
}
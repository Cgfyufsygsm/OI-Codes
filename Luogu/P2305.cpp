#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

typedef long long ll;
typedef double db;

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    ll read() {
        ll s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

il ll min(ll a, ll b) {return a < b ? a : b;}
il ll max(ll a, ll b) {return a > b ? a : b;}

const int maxn = 2e5 + 5;

int n, head[maxn], to[maxn], nxt[maxn], cnte, fa[maxn];
ll p[maxn], q[maxn], dis[maxn], lim[maxn];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int maxp[maxn], root, vis[maxn], size[maxn];
ll f[maxn];

void getRoot(int u, int m) {
    size[u] = 1, maxp[u] = 0;
    GO(u) {
        if (vis[v]) continue;
        getRoot(v, m);
        size[u] += size[v];
        maxp[u] = max(maxp[u], size[v]);
    }
    maxp[u] = max(maxp[u], m - size[u]);
    if (maxp[u] <= maxp[root]) root = u;
    return;
}

void getDis(int u) {
    GO(u) {
        dis[v] += dis[u];
        getDis(v);
    }
    return;
}

int son[maxn], cnt, stk[maxn], top;

void getSon(int u) {
    son[++cnt] = u;
    GO(u)
        if (!vis[v]) getSon(v);
    return;
}

il bool cmp(int u, int v) {
    return dis[u] - lim[u] > dis[v] - lim[v];
}

il db slope(int u, int v) {return db(f[u] - f[v]) / db(dis[u] - dis[v]);}

void insert(int u) {
    while (top >= 2 && slope(stk[top - 1], stk[top]) <= slope(stk[top], u)) --top;
    stk[++top] = u;
    return;
}

int query(db x) {
    int l = 1, r = top, mid, ret = top;
    while (l < r) {
        mid = (l + r) >> 1;
        if (slope(stk[mid], stk[mid + 1]) <= x) r = mid, ret = mid;
        else l = mid + 1;
    }
    return stk[ret];
}

void solve(int u, int m) {
    if (m == 1) return;
    root = 0, maxp[0] = n, getRoot(u, m);
    int x = root;
    GO(x) vis[v] = 1, m -= size[v];
    solve(u, m);
    cnt = 0;
    GO(x) getSon(v);
    std::sort(son + 1, son + cnt + 1, cmp);

    int j = x;
    top = 0;
    FOR(i, 1, cnt) {
        int y = son[i];
        while (j != fa[u] && dis[j] >= dis[y] - lim[y]) insert(j), j = fa[j];
        if (top) {
            int x = query(p[y]);
            f[y] = min(f[y], f[x] + p[y] * (dis[y] - dis[x]) + q[y]);
        }
    }

    GO(x) solve(v, size[v]);
    return;
}

int main() {
    n = read(), read();
    FOR(i, 2, n) {
        add(fa[i] = read(), i);
        dis[i] = read(), p[i] = read(), q[i] = read(), lim[i] = read();
        f[i] = 1e18;
    }
    getDis(1);
    solve(1, n);
    FOR(i, 2, n) printf("%lld\n", f[i]);
    return 0;
}
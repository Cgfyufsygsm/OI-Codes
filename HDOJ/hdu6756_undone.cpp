#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <vector>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define clr(a) memset(a, 0, sizeof a)
#define lowbit(x) (x & -x)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

const int maxn = 1e5 + 5, sqrtN = 325;
int block, n, m;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int a[maxn], deg[maxn];
std::vector<int> g[maxn], tree[maxn], vis[maxn];//与之相连的大点，树状数组

il void addEdge(int u, int v) {
    ++deg[v];
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void modify(int u, int x, int val) {
    for (; x <= block + 5; x += lowbit(x))
        tree[u][x] += val;
    return;
}

int sum(int u, int x) {
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree[u][x];
    return ret;
}
void init() {
    n = read(), m = read();
    block = sqrt(n);
    FOR(i, 1, n) a[i] = read(), g[i].clear(), tree[i].clear(), vis[i].clear();
    clr(deg), clr(head), cnte = 0;
    FOR(i, 1, m) {
        int u = read(), v = read();
        addEdge(u, v), addEdge(v, u);
    }
    FOR(u, 1, n)
        if (deg[u] > block) {
            tree[u].resize(block + 10), vis[u].resize(block + 10);
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                g[v].push_back(u);
                if (a[v] <= deg[u]) {
                    if (!vis[u][a[v]])
                        modify(u, a[v], 1);
                    ++vis[u][a[v]];
                }
            }
        }
    return;
}

void solve() {
    int q = read();
    while (q--) {
        int op = read();
        if (op == 1) {
            int u = read(), x = read() + 1;
            for (auto v : g[u]) {
                if (x <= deg[v]) {
                    if (!vis[v][x]++)
                        modify(v, x, 1);
                }
                if (a[u] <= deg[v]) {
                    if (!--vis[v][a[u]])
                        modify(v, a[u], -1);
                }
            }
            a[u] = x;
        } else {
            int u = read();
            if (deg[u] > block) {
                int l = 1, r = deg[u], mid, ans;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    if (sum(u, mid) < mid) ans = mid, r = mid - 1;
                    else l = mid + 1;
                }
                printf("%d\n", ans - 1);
            } else {
                int cnt[sqrtN];
                clr(cnt);
                for (int i = head[u]; i; i = nxt[i])
                    if (a[to[i]] <= block)
                        ++cnt[a[to[i]]];
                int ans = 1;
                while (cnt[ans]) ++ans;
                printf("%d\n", ans - 1);
            }
        }
    }
    return;
}

int main() {
    int T = read();
    while (T--) {
        init();
        solve();
    }
    return 0;
}
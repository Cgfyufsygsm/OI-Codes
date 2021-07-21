#include <cstdio>
#include <cctype>
#include <vector>
#include <set>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
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

const int maxn = 1e5 + 5, block = 1000;
int n, m;
int a[maxn], deg[maxn], id[maxn], cnt, tmp[1005], vis[105][maxn];
std::vector<int> g[maxn];
std::set<int> s[105];

void init() {
    n = read(), m = read();
    FOR(i, 1, n) a[i] = read(), g[i].clear(), deg[i] = 0, id[i] = 0;
    cnt = 0;
    FOR(i, 1, m) {
        int u = read(), v = read();
        g[u].push_back(v), g[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    FOR(u, 1, n) {
        if (deg[u] >= block) {
            ++cnt;
            id[u] = cnt, s[cnt].clear();
            FOR(i, 0, deg[u]) s[cnt].insert(i), vis[cnt][i] = 0;
            for (auto v : g[u]) {
                if (a[v] <= deg[u]) {
                    ++vis[cnt][a[v]];
                    s[cnt].erase(a[v]);
                }
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
            int u = read(), x = read();
            for (auto v : g[u]) {
                if (!id[v]) continue;
                if (x <= deg[v]) {
                    ++vis[id[v]][x];
                    s[id[v]].erase(x);
                }
                if (a[u] <= deg[v])
                    if (!--vis[id[v]][a[u]])
                        s[id[v]].insert(a[u]);
            }
            a[u] = x;
        } else {
            int u = read();
            if (id[u]) 
                printf("%d\n", *s[id[u]].begin());
            else {
                for (auto v : g[u])
                    if (a[v] <= deg[u])
                        tmp[a[v]] = 1;
                int ans = 0;
                FOR(i, 0, deg[u]) {
                    if (!tmp[i]) {
                        ans = i;
                        break;
                    }
                }
                for (auto v : g[u])
                    if (a[v] <= deg[u])
                        tmp[a[v]] = 0;
                printf("%d\n", ans);
            }
        }
    }
}

int main() {
    int T = read();
    while (T--) {
        init();
        solve();
    }
    return 0;
}
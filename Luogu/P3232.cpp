#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
}

using namespace fastIO;
typedef double db;

const int maxn = 505, maxm = 125005;

db a[maxn][maxn], f[maxn];
int n, m, deg[maxn];

struct edge {
    int u, v;
    double g;
    il bool operator<(const edge &b) const {return g > b.g;}
} e[maxm];
std::vector<int> G[maxn];

il void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
    return;
}

void gauss() {
    FOR(i, 1, n - 1) {
        int r = i;
        FOR(j, i + 1, n - 1)
            if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        std::swap(a[i], a[r]);
        FOR(k, 1, n - 1) {
            if (k == i) continue;
            db div = a[k][i] / a[i][i];
            FOR(j, i + 1, n)
                a[k][j] -= div * a[i][j];
        }
    }
    FOR(i, 1, n - 1) f[i] = a[i][n] / a[i][i];
    return;
}

int main() {
    read(n), read(m);
    FOR(i, 1, m) read(e[i].u), read(e[i].v), ++deg[e[i].u], ++deg[e[i].v], addEdge(e[i].u, e[i].v);
    FOR(u, 1, n - 1) {
        a[u][u] = -1;
        if (u == 1) a[u][n] = -1;
        for (auto v : G[u]) if (v != n) a[u][v] = 1.00 / deg[v];
    }
    
    gauss();
    FOR(i, 1, m) e[i].g = f[e[i].u] / deg[e[i].u] + f[e[i].v] / deg[e[i].v];
    std::sort(e + 1, e + m + 1);
    db ans = 0;
    FOR(i, 1, m) ans += i * e[i].g;
    printf("%.3lf\n", ans);
    return 0;
}
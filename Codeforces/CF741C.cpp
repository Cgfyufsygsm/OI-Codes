#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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
}

using namespace fastIO;

const int maxn = 1e6 + 5;
int n, G[maxn][2], x[maxn], y[maxn];
int vis[maxn], ans[maxn];

void dfs(int u, int col) {
    ans[u] = col;
    vis[u] = 1;
    FOR(k, 0, 1) {
        int v = G[u][k];
        if (!vis[v]) dfs(v, col ^ 1);
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) {
        read(x[i]), read(y[i]);
        G[x[i]][0] = y[i], G[y[i]][0] = x[i];
    }
    for (int i = 1; i < 2 * n; i += 2) G[i][1] = i + 1;
    for (int i = 2; i <= 2 * n; i += 2) G[i][1] = i - 1;
    FOR(i, 1, 2 * n) {
        if (!vis[i]) dfs(i, 1);
    }
    FOR(i, 1, n) print(ans[x[i]] ? 1 : 2), putchar(' '), print(ans[y[i]] ? 1 : 2), putchar('\n');
    return output(), 0;
}
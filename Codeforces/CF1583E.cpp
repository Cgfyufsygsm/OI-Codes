#include <cstdio>
#include <cctype>
#include <vector>
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
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void print(const char str[]) {
    for (int i = 0; str[i]; ++i) putchar(str[i]);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 3e5 + 5;
int fa[maxn][22], n, m, q, dep[maxn], vis[maxn], a[maxn][2], deg[maxn];
std::vector<int> G[maxn];

void dfs(int u, int pre) {
    fa[u][0] = pre;
    for (int i = 1; fa[fa[u][i - 1]][i - 1]; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    dep[u] = dep[pre] + 1, vis[u] = 1;
    for (auto v : G[u]) {
        if (vis[v]) continue;
        dfs(v, u);
    }
    return;
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) myswap(u, v);
    DEC(i, 20, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    DEC(i, 20, 0) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}

void find(int u, int to, std::vector<int> &vec) {
    while (u != to) {
        vec.push_back(u);
        u = fa[u][0];
    }
    return;
}

int main() {
    read(n), read(m);
    FOR(i, 1, m) {
        int x, y; read(x), read(y);
        G[x].push_back(y), G[y].push_back(x);
    }
    dfs(1, 0);

    read(q);
    FOR(i, 1, q) read(a[i][0]), read(a[i][1]), ++deg[a[i][0]], ++deg[a[i][1]];

    int ans = 0;
    FOR(i, 1, n) ans += (deg[i] & 1);
    if (!ans) {
        print("YES\n");
        FOR(i, 1, q) {
            std::vector<int> p1, p2;
            int l = LCA(a[i][0], a[i][1]);
            find(a[i][0], l, p1), find(a[i][1], l, p2);
            print(p1.size() + p2.size() + 1, '\n');
            for (auto x : p1) print(x, ' ');
            print(l, ' ');
            DEC(i, (int)p2.size() - 1, 0) print(p2[i], ' ');
            putchar('\n');
        }
    } else print("NO\n"), print(ans / 2, '\n');
    return output(), 0;
}
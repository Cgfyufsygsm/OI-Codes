#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 2e5 + 5;
struct edge {
    int u, v, w;
    edge() {}
    edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
} e[maxn];
int n, m, q, ufs[maxn], dep[maxn], fa[maxn][19], maxt[maxn][19];
vector<edge> G[maxn];

int find(int u) {return ufs[u] == u ? u : ufs[u] = find(ufs[u]);}

void dfs(int u, int f, int val) {
    fa[u][0] = f, maxt[u][0] = val, dep[u] = dep[f] + 1;
    FOR(j, 1, 18) fa[u][j] = fa[fa[u][j - 1]][j - 1], maxt[u][j] = max(maxt[fa[u][j - 1]][j - 1], maxt[u][j - 1]);
    for (auto e : G[u]) {
        if (e.v == f) continue;
        dfs(e.v, u, e.w);
    }
    return;
}

int query(int u, int v) {
    int ans = 0;
    if (dep[u] < dep[v]) swap(u, v);
    DEC(i, 18, 0) {
        if (dep[fa[u][i]] >= dep[v]) chkmax(ans, maxt[u][i]), u = fa[u][i];
        if (u == v) return ans;
    }
    DEC(i, 18, 0) {
        if (fa[u][i] != fa[v][i])
            chkmax(ans, max(maxt[u][i], maxt[v][i])), u = fa[u][i], v = fa[v][i];
    }
    return max(ans, maxt[u][0], maxt[v][0]);
}

int main() {
    read(n, m, q);
    FOR(i, 1, n) ufs[i] = i;
    FOR(i, 1, m)
        read(e[i].u, e[i].v, e[i].w);
    sort(e + 1, e + m + 1, [](const edge &a, const edge &b) {return a.w < b.w;});
    FOR(i, 1, m) {
        if (find(e[i].u) != find(e[i].v)) {
            ufs[find(e[i].u)] = find(e[i].v);
            G[e[i].u].push_back(edge(e[i].u, e[i].v, e[i].w));
            G[e[i].v].push_back(edge(e[i].v, e[i].u, e[i].w));
        }
    }
    dfs(1, 0, 0);
    while (q--) {
        int u, v, w; read(u, v, w);
        int w0 = query(u, v);
        print(w0 > w ? "Yes" : "No");
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
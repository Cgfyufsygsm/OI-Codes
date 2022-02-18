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
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 1e5 + 5, maxm = 3e5 + 5;

struct Edge0 {
    int u, v; ll w;
} e0[maxm];

struct Edge : Edge0 {
    int &to = v, &nxt = u;
} e[maxn << 1];
int head[maxn], cnte, n, m, inTree[maxm];
int ufs[maxn];

int find(int u) {return ufs[u] == u ? u : ufs[u] = find(ufs[u]);}

il void add(int u, int v, ll w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

int fa[maxn], dep[maxn], size[maxn], son[maxn], dfn[maxn], top[maxn], dfntot, lg[maxn];

struct Node {
    ll maxv, max2v;
    Node(int x = -1, int y = -1) : maxv(x), max2v(y) {}
} st[18][maxn];

void dfs1(int u, int pre) {
    fa[u] = pre, dep[u] = dep[pre] + 1, size[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == pre) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf, ll prew) {
    top[u] = topf, dfn[u] = ++dfntot, st[0][dfn[u]] = Node(prew, -1);
    for (int i = head[u]; i; i = e[i].nxt) if (e[i].to == son[u]) {
        dfs2(son[u], topf, e[i].w);
        break;
    }
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v, e[i].w);
    }
    return;
}

il Node operator+(const Node &a, const Node &b) {
    Node ret;
    ret.maxv = max(a.maxv, b.maxv), ret.max2v = -1;
    if (a.maxv != ret.maxv) chkmax(ret.max2v, a.maxv);
    if (a.max2v != ret.maxv) chkmax(ret.max2v, a.max2v);
    if (b.maxv != ret.maxv) chkmax(ret.max2v, b.maxv);
    if (b.max2v != ret.maxv) chkmax(ret.max2v, b.max2v);
    return ret;
}

void build() {
    lg[0] = -1;
    FOR(i, 1, n) lg[i] = lg[i >> 1] + 1;
    FOR(j, 1, 17) FOR(i, 1, n - (1 << j) + 1) st[j][i] = st[j - 1][i] + st[j - 1][i + (1 << (j - 1))];
    return;
}

il Node queryST(int l, int r) {
    if (l > r) return Node();
    int s = lg[r - l + 1];
    return st[s][l] + st[s][r - (1 << s) + 1];
}

Node query(int u, int v) {
    Node ret; ret.maxv = ret.max2v = -1;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = ret + queryST(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ret = ret + queryST(dfn[u] + 1, dfn[v]);
    return ret;
}

int main() {
    read(n, m);
    FOR(i, 1, n) ufs[i] = i;
    FOR(i, 1, m)
        read(e0[i].u, e0[i].v, e0[i].w);
    sort(e0 + 1, e0 + m + 1, [](const auto &a, const auto &b) {return a.w < b.w;});
    ll mst = 0;
    FOR(i, 1, m) {
        int &u = e0[i].u, &v = e0[i].v;
        if (find(u) == find(v)) continue;
        ufs[find(u)] = find(v), add(u, v, e0[i].w), add(v, u, e0[i].w), inTree[i] = 1, mst += e0[i].w;
    }
    dfs1(1, 0), dfs2(1, 1, 0), build();
    ll ans = 1e18;
    FOR(i, 1, m) if (!inTree[i] && e0[i].u != e0[i].v) {
        Node ret = query(e0[i].u, e0[i].v);
        if (ret.maxv == e0[i].w) {
            if (ret.max2v == -1) continue;
            else chkmin(ans, mst - ret.max2v + e0[i].w);
        } else chkmin(ans, mst - ret.maxv + e0[i].w);
    }
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
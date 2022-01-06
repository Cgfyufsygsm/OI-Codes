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

const int maxn = 1e5 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int n, q, v0[maxn], dfn[maxn], dfnClock, dep[maxn], size[maxn], fa[maxn], top[maxn], son[maxn];
int root1[maxn], root2[maxn], tot;
//root1 关于树上前缀，root2 关于 dfn

struct node {
    int ch[2], size;
} t[maxn * 100];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int clone(int u) {
    t[++tot] = t[u];
    return tot;
}

int insert(int u, int k, int val) {
    u = clone(u);
    ++t[u].size;
    int c = (val >> k) & 1;
    if (~k) t[u].ch[c] = insert(t[u].ch[c], k - 1, val);
    return u;
}

void dfs1(int u, int f) {
    dfn[u] = ++dfnClock, dep[u] = dep[f] + 1, size[u] = 1, fa[u] = f;
    root2[dfn[u]] = insert(root2[dfn[u] - 1], 30, v0[u]);
    root1[u] = insert(root1[f], 30, v0[u]);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    else return;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
    return;
}

int getLCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int query(int l, int r, int val, int k) {
    if (k < 0) return 0;
    int c = (val >> k) & 1;
    if (t[t[r].ch[c ^ 1]].size - t[t[l].ch[c ^ 1]].size)
        return query(t[l].ch[c ^ 1], t[r].ch[c ^ 1], val, k - 1) | (1 << k);
    else return query(t[l].ch[c], t[r].ch[c], val, k - 1);
}

int main() {
    read(n, q);
    FOR(i, 1, n) read(v0[i]);
    FOR(i, 1, n - 1) {
        int u, v; read(u, v);
        add(u, v), add(v, u);
    }
    dfs1(1, 0), dfs2(1, 1);
    while (q--) {
        int op; read(op);
        if (op == 1) {
            int x, z; read(x, z);
            print(query(root2[dfn[x] - 1], root2[dfn[x] + size[x] - 1], z, 30));
        } else {
            int x, y, z; read(x, y, z);
            int lca = fa[getLCA(x, y)];
            print(max(query(root1[lca], root1[x], z, 30), query(root1[lca], root1[y], z, 30)));
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
//il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
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
//il void putchar(char c) {*__pO++ = c;}
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

const int maxn = 2e5 + 5;
int n, m, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int val[maxn], st[19][maxn << 1], dep[maxn], dfnCnt, lg[maxn << 1], pos[maxn];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1;
    st[0][++dfnCnt] = u;
    pos[u] = dfnCnt;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == pre) continue;
        dfs0(v, u);
        st[0][++dfnCnt] = u;
    }
    return;
}

void initST() {
    lg[0] = -1;
    FOR(i, 1, dfnCnt) lg[i] = lg[i >> 1] + 1;
    FOR(j, 1, lg[dfnCnt])
        FOR(i, 1, dfnCnt - (1 << j) + 1)
            st[j][i] = dep[st[j - 1][i]] < dep[st[j - 1][i + (1 << (j - 1))]] ? st[j - 1][i] : st[j - 1][i + (1 << (j - 1))];
    return;
}

int getDis(int u, int v) {
    int l = min(pos[u], pos[v]), r = max(pos[u], pos[v]);
    int len = lg[r - l + 1];
    int lca = dep[st[len][l]] < dep[st[len][r - (1 << len) + 1]] ? st[len][l] : st[len][r - (1 << len) + 1];
    return dep[u] + dep[v] - 2 * dep[lca];
}

int root, maxp[maxn], size[maxn], tot, fa[maxn], vis[maxn];

void getRt(int u, int pre) {
    size[u] = 1, maxp[u] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == pre || vis[v]) continue;
        getRt(v, u);
        size[u] += size[v];
        chkmax(maxp[u], size[v]);
    }
    chkmax(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

vector<int> t[2][maxn];

#define lowbit(x) (x & -x)

void update(vector<int> &t, int x, int v) {
    for (++x; x < (int)t.size(); x += lowbit(x)) t[x] += v;
    return;
}

int query(vector<int> &t, int x) {
    int ret = 0;
    for (x = min(x + 1, (int)t.size() - 1); x; x -= lowbit(x)) ret += t[x];
    return ret;
}

void dfs(int u) {
    vis[u] = 1;
    t[0][u].resize(size[u] / 2 + 2);
    t[1][u].resize(size[u] + 2);
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (vis[v]) continue;
        maxp[root = 0] = n, tot = size[v];
        getRt(v, 0), getRt(root, 0);
        fa[root] = u;
        dfs(root);
    }
}

void modify(int x, int v) {
    for (int u = x; u; u = fa[u]) update(t[0][u], getDis(x, u), v);
    for (int u = x; fa[u]; u = fa[u]) update(t[1][u], getDis(fa[u], x), v);
    return;
}

int main() {
    read(n, m);
    FOR(i, 1, n) read(val[i]);
    FOR(i, 2, n) {
        int u, v; read(u, v);
        add(u, v), add(v, u);
    }
    dfs0(1, 0);
    initST();
    maxp[root = 0] = tot = n;
    getRt(1, 0), getRt(root, 0);
    dfs(root);
    FOR(i, 1, n) modify(i, val[i]);
    int lastans = 0;
    while (m--) {
        int op, x, y; read(op, x, y);
        x ^= lastans, y ^= lastans;
        if (!op) {
            lastans = query(t[0][x], y);
            for (int u = x; fa[u]; u = fa[u]) {
                int dis = getDis(x, fa[u]);
                if (y >= dis) lastans += query(t[0][fa[u]], y - dis) - query(t[1][u], y - dis);
            }
            print(lastans);
        } else modify(x, y - val[x]), val[x] = y;
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
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

const int maxn = 3e5 + 5;
int fa[maxn], size[maxn], son[maxn], top[maxn], dep[maxn], dis[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], w[maxn << 1], cnte, n, m;
struct Chain {
    int u, v, len, lca;
} c[maxn];

il void add(int u, int v, int l) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    w[cnte] = l;
    head[u] = cnte;
    return;
}

void dfs1(int u, int pre) {
    fa[u] = pre, size[u] = 1, dep[u] = dep[pre] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == pre) continue;
        dis[v] = dis[u] + w[i];
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa[u] || v == son[u]) continue;
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

int sum[maxn];

void dfs3(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        if (to[i] == fa[u]) continue;
        dfs3(to[i]);
        sum[u] += sum[to[i]];
    }
    return;
}

bool check(int mid) {
    memset(sum, 0, sizeof sum);
    int cnt = 0;
    FOR(i, 1, m) {
        if (c[i].len <= mid) break;
        ++sum[c[i].u], ++sum[c[i].v], sum[c[i].lca] -= 2;
        ++cnt;
    }
    dfs3(1);
    FOR(i, 2, n)
        if (sum[i] == cnt && c[1].len - dis[i] + dis[fa[i]] <= mid) return true;
    return false;
}

int main() {
    read(n, m);
    FOR(i, 1, n - 1) {
        int u, v, w; read(u, v, w);
        add(u, v, w), add(v, u, w);
    }
    dfs1(1, 0), dfs2(1, 1);
    FOR(i, 1, m) {
        read(c[i].u, c[i].v);
        c[i].len = dis[c[i].u] + dis[c[i].v] - 2 * dis[c[i].lca = getLCA(c[i].u, c[i].v)];
    }
    sort(c + 1, c + n + 1, [](const Chain &a, const Chain &b) {return a.len > b.len;});
    int l = 0, r = c[1].len + 1, ans = c[1].len;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid;
        else l = mid + 1;
    }
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
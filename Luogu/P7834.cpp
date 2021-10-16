#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int maxn = 2e5 + 5, maxm = 5e5 + 5;
int n, m, q, a0[maxn], a[maxn];
int ufs[maxn];
int head[maxn], to[maxn], nxt[maxn], cnte, tot;
int fa[maxn][23], dfn[maxn], low[maxn], nfd[maxn], dfnClock, dis[maxn], size[maxn];

il int find(int u) {return u == ufs[u] ? u : ufs[u] = find(ufs[u]);}

struct edge {
    int u, v, w;
} e[maxm];

void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int f) {
    fa[u][0] = f;
    FOR(i, 1, 22) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    dfn[u] = ++dfnClock;
    nfd[dfn[u]] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        dfs(v, u);
        size[u] += size[v];
    }
    if (!size[u]) size[u] = 1;
    low[u] = dfnClock;
    return;
}

void kruskal() {
    FOR(i, 1, n) ufs[i] = i;
    tot = n;
    std::sort(e + 1, e + m + 1, [](const edge &a, const edge &b) -> bool {return a.w < b.w;});
    FOR(i, 1, m) {
        int u = e[i].u, v = e[i].v;
        u = find(u), v = find(v);
        if (u == v) continue;
        ++tot;
        ufs[tot] = ufs[u] = ufs[v] = tot;
        add(tot, u), add(tot, v);
        dis[tot] = e[i].w;
    }
    dfs(tot, 0);
    return;
}

struct node {
    int ls, rs, sum;
} t[maxn << 6];

int root[maxn];

#define ls(k) (t[k].ls)
#define rs(k) (t[k].rs)
#define M ((i + j) >> 1)

il int clone(int k) {
    static int cnt = 0;
    t[++cnt] = t[k];
    return cnt;
}

int insert(int k, int i, int j, int x) {
    k = clone(k);
    ++t[k].sum;
    if (i == j) return k;
    if (x <= M) ls(k) = insert(ls(k), i, M, x);
    else rs(k) = insert(rs(k), M + 1, j, x);
    return k;
}

int query(int k1, int k2, int i, int j, int x) {
    if (i == j) return i;
    int sz = t[rs(k2)].sum - t[rs(k1)].sum;
    if (sz < x) return query(ls(k1), ls(k2), i, M, x - sz);
    else return query(rs(k1), rs(k2), M + 1, j, x);
}

int main() {
    read(n), read(m), read(q);
    FOR(i, 1, n) read(a0[i]), a[i] = a0[i];
    FOR(i, 1, m) read(e[i].u), read(e[i].v), read(e[i].w);
    kruskal();

    std::sort(a0 + 1, a0 + n + 1);
    int cnt = std::unique(a0 + 1, a0 + n + 1) - a0 - 1;

    FOR(i, 1, tot) {
        if (nfd[i] <= n) root[i] = insert(root[i - 1], 1, cnt, std::lower_bound(a0 + 1, a0 + cnt + 1, a[nfd[i]]) - a0);
        else root[i] = root[i - 1];
    }

    int last = 0;
    while (q--) {
        int u, x, k;
        read(u), read(x), read(k);
        u = (u ^ last) % n + 1, x ^= last, k = (k ^ last) % n + 1;
        DEC(j, 22, 0) {
            if (fa[u][j] && dis[fa[u][j]] <= x)
                u = fa[u][j];
        }
        if (k > size[u]) last = 0, print(-1, '\n');
        else print(last = a0[query(root[dfn[u] - 1], root[low[u]], 1, cnt, k)], '\n');
    }
    return output(), 0;
}
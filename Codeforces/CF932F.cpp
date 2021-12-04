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
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
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

using ll = long long;
const int maxn = 2e5 + 5, N = 1e5;
const ll INF = 0x7fffffffffffffff;
int n, root[maxn];
ll a[maxn], b[maxn], f[maxn];
vector<int> G[maxn];

int tot = 0, ls[maxn << 5], rs[maxn << 5], t[maxn << 5];
il ll calc(ll x, int u) {return b[u] * x + f[u];}

#define M ((i + j) >> 1)

void insert(int &k, int i, int j, int u) {
    if (!k) return k = ++tot, t[k] = u, void();
    if (calc(M, t[k]) > calc(M, u)) swap(u, t[k]);
    if (calc(i, t[k]) <= calc(i, u) && calc(j, t[k]) <= calc(j, u)) return;
    if (calc(i, t[k]) > calc(i, u)) insert(ls[k], i, M, u);
    else insert(rs[k], M + 1, j, u);
    return;
}

int merge(int x, int y, int i, int j) {
    if (!x || !y) return x + y;
    insert(x, i, j, t[y]);
    ls[x] = merge(ls[x], ls[y], i, M);
    rs[x] = merge(rs[x], rs[y], M + 1, j);
    return x;
}

ll query(int k, int i, int j, ll x) {
    if (!k) return INF;
    return min(calc(x, t[k]), x <= M ? query(ls[k], i, M, x) : query(rs[k], M + 1, j, x));
}

void dfs(int u, int fa) {
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v], -N, N);
    }
    f[u] = query(root[u], -N, N, a[u]);
    if (f[u] == INF) f[u] = 0;
    insert(root[u], -N, N, u);
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]);
    FOR(i, 1, n - 1) {
        int u, v; read(u, v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    FOR(i, 1, n) print(f[i], ' ');
    return output(), 0;
}

} // namespace YangTY

signed main() {
    YangTY::main();
    return 0;
}
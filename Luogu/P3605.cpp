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

const int maxn = 1e5 + 5;

struct node {
    int sum, ls, rs;
} t[maxn * 100];

#define ls(u) t[u].ls
#define rs(u) t[u].rs
#define M ((i + j) >> 1)

int n, p0[maxn], p[maxn], rt[maxn], cnt;

il void pushup(int k) {
    t[k].sum = t[ls(k)].sum + t[rs(k)].sum;
    return;
}

void modify(int i, int j, int &k, int x, int val) {
    if (!k) k = ++cnt;
    if (i == j) {
        t[k].sum += val;
        return;
    }
    if (x <= M) modify(i, M, ls(k), x, val);
    else modify(M + 1, j, rs(k), x, val);
    pushup(k);
    return;
}

int merge(int i, int j, int k1, int k2) {
    if (!k1 || !k2) return k1 | k2;
    if (i == j) {
        t[k1].sum += t[k2].sum;
        return k1;
    }
    ls(k1) = merge(i, M, ls(k1), ls(k2));
    rs(k1) = merge(M + 1, j, rs(k1), rs(k2));
    return pushup(k1), k1;
}

int query(int i, int j, int k, int x, int y) {
    if (!k) return 0;
    if (x <= i && y >= j) return t[k].sum;
    int ret = 0;
    if (x <= M) ret += query(i, M, ls(k), x, y);
    if (y > M) ret += query(M + 1, j, rs(k), x, y);
    return ret;
}

vector<int> G[maxn];
int ans[maxn];

void dfs(int u) {
    int nowp = lower_bound(p0 + 1, p0 + n + 1, p[u]) - p0;
    modify(1, n, rt[u], nowp, 1);
    for (auto v : G[u]) {
        dfs(v);
        rt[u] = merge(1, n, rt[u], rt[v]);
    }
    ans[u] = query(1, n, rt[u], nowp + 1, n);
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) read(p0[i]), p[i] = p0[i];
    sort(p0 + 1, p0 + n + 1);
    FOR(i, 2, n) {
        int f; read(f);
        G[f].push_back(i);
    }
    dfs(1);
    FOR(i, 1, n) print(ans[i]);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
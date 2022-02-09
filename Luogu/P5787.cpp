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

using pii = pair<int, int>;
const int maxn = 1e5 + 5;
int n, m, k;
bool flag;

struct UnionFind {
    int fa[maxn], sz[maxn], w[maxn], top;
    pii stk[maxn];
    void init() {
        FOR(i, 1, n) fa[i] = i, sz[i] = 1;
    }
    int find(int x, int &d) {
        if (x == fa[x]) return x;
        d ^= w[x];
        return find(fa[x], d);
    }
    void merge(int x, int y) {
        int dx = 0, dy = 0;
        x = find(x, dx), y = find(y, dy);
        if (x == y) return flag |= (dx == dy), void();
        if (sz[x] > sz[y]) swap(x, y);
        sz[y] += sz[x], fa[x] = y, w[x] = (dx ^ dy ^ 1);
        stk[++top] = pii(x, y);
    }
    void undo(int tar) {
        while (top > tar) {
            auto &now = stk[top--];
            fa[now.first] = now.first;
            w[now.first] = 0;
            sz[now.second] -= sz[now.first];
        }
        return;
    }
} ufs;

vector<pii> t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int y, pii e) {
    if (x <= i && y >= j) {
        t[k].push_back(e);
        return;
    }
    if (x <= M) modify(i, M, L, x, y, e);
    if (y > M) modify(M + 1, j, R, x, y, e);
    return;
}

void dfs(int i, int j, int k) {
    int now = ufs.top, nowf = flag;
    for (auto &p : t[k]) ufs.merge(p.first, p.second);
    if (i == j) {
        print(flag ? "No" : "Yes");
        flag = nowf, ufs.undo(now);
        return;
    }
    dfs(i, M, L), dfs(M + 1, j, R);
    flag = nowf, ufs.undo(now);
    return;
}

int main() {
    read(n, m, k);
    ufs.init();
    FOR(i, 1, m) {
        int x, y, l, r; read(x, y, l, r);
        modify(1, k, 1, l + 1, r, pii(x, y));
    }
    dfs(1, k, 1);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
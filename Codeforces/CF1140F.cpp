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
using pii = pair<int, int>;
const int maxn = 3e5 + 5, N = 3e5;
ll ans[maxn], nowAns;

struct UnionFind {
    int fa[maxn << 1], top;
    ll cntl[maxn << 1], cntr[maxn << 1];
    pii stk[maxn << 1];
    UnionFind() {
        FOR(i, 1, N << 1) fa[i] = i;
        FOR(i, 1, N) cntl[i] = cntr[i + N] = 1;
    }
    int find(int x) {return x == fa[x] ? x : find(fa[x]);}
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (cntl[x] + cntr[x] > cntl[y] + cntr[y]) swap(x, y);
        nowAns -= cntl[x] * cntr[x] + cntl[y] * cntr[y];
        fa[x] = y, cntl[y] += cntl[x], cntr[y] += cntr[x];
        nowAns += cntl[y] * cntr[y];
        stk[++top] = {x, y};
        return;
    }
    void undo(int tar) {
        while (top > tar) {
            int x = stk[top].first, y = stk[top].second;
            --top;
            nowAns -= cntl[y] * cntr[y];
            fa[x] = x, cntl[y] -= cntl[x], cntr[y] -= cntr[x];
            nowAns += cntl[x] * cntr[x] + cntl[y] * cntr[y];
        }
        return;
    }
} ufs;

map<int, int> exist[maxn];
vector<pii> t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int y, pii p) {
    if (x <= i && y >= j) {
        t[k].push_back(p);
        return;
    }
    if (x <= M) modify(i, M, L, x, y, p);
    if (y > M) modify(M + 1, j, R, x, y, p);
    return;
}

void dfs(int i, int j, int k) {
    int now = ufs.top;
    for (auto &p : t[k]) ufs.merge(p.first, p.second + N);
    if (i == j) {
        ans[i] = nowAns;
        ufs.undo(now);
        return;
    }
    dfs(i, M, L), dfs(M + 1, j, R);
    ufs.undo(now);
    return;
}

int main() {
    int T; read(T);
    FOR(i, 1, T) {
        int x, y; read(x, y);
        if (exist[x].count(y)) modify(1, T, 1, exist[x][y], i - 1, {x, y}), exist[x].erase(y);
        else exist[x][y] = i;
    }
    FOR(x, 1, N) for (auto &p : exist[x]) modify(1, T, 1, p.second, T, {x, p.first});
    dfs(1, T, 1);
    FOR(i, 1, T) print(ans[i], ' ');
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
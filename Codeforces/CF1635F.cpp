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
using pll = pair<ll, ll>;
const int maxn = 3e5 + 5;
int n, m, L[maxn], R[maxn], stk[maxn], top;
ll t[maxn << 2], ans[maxn];
pll a[maxn];
vector<pll> op[maxn], q[maxn];

il ll calc(int i, int j) {return myabs(a[i].first - a[j].first) * (a[i].second + a[j].second);}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, ll v) {
    if (i == j) {
        chkmin(t[k], v);
        return;
    }
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    t[k] = min(t[L], t[R]);
    return;
}

ll query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    ll ret = 2e18;
    if (x <= M) chkmin(ret, query(i, M, L, x, y));
    if (y > M) chkmin(ret, query(M + 1, j, R, x, y));
    return ret;
}

#undef L
#undef R
#undef M

int main() {
    read(n, m);
    FOR(i, 1, n) read(a[i].first, a[i].second);
    FOR(i, 1, m) {
        int l, r; read(l, r);
        q[r].push_back({l, i});
    }
    FOR(i, 1, n) {
        while (top > 0 && a[stk[top]].second > a[i].second) --top;
        L[i] = stk[top], stk[++top] = i;
    }
    top = 0;
    DEC(i, n, 1) {
        while (top > 0 && a[stk[top]].second > a[i].second) --top;
        R[i] = stk[top], stk[++top] = i;
    }
    FOR(i, 1, n) {
        if (L[i]) op[i].push_back({L[i], calc(L[i], i)});
        if (R[i]) op[R[i]].push_back({i, calc(i, R[i])});
    }

    memset(t, 0x3f, sizeof t);
    FOR(i, 1, n) {
        for (auto &p : op[i]) modify(1, n, 1, p.first, p.second);
        for (auto &p : q[i]) ans[p.second] = query(1, n, 1, p.first, i);
    }
    FOR(i, 1, m) print(ans[i]);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
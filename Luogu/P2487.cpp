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

using db = double;
const int maxn = 5e4 + 5;
struct node {
    int t, h, v;
} a[maxn];
int n, v0[maxn];
int f1[maxn], f2[maxn];
db g1[maxn], g2[maxn], sum;
auto cmpt = [](const node &lhs, const node &rhs) {return lhs.t < rhs.t;};
auto cmph = [](const node &lhs, const node &rhs) {return (lhs.h == rhs.h) ? lhs.t < rhs.t : lhs.h >= rhs.h;};

struct segtree {
    int maxv;
    db cnt;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void clear(int i, int j, int k) {
    if (!t[k].maxv) return;
    t[k].maxv = 0;
    if (i == j) return;
    clear(i, M, L), clear(M + 1, j, R);
    return;
}

void update(int i, int j, int k, int x, int v, db v2) {
    if (i == j) {
        if (t[k].maxv < v) t[k].maxv = v, t[k].cnt = 0;
        if (t[k].maxv == v) t[k].cnt += v2;
        return;
    }
    if (x <= M) update(i, M, L, x, v, v2);
    else update(M + 1, j, R, x, v, v2);
    t[k].maxv = max(t[L].maxv, t[R].maxv);
    t[k].cnt = 0;
    if (t[k].maxv == t[L].maxv) t[k].cnt += t[L].cnt;
    if (t[k].maxv == t[R].maxv) t[k].cnt += t[R].cnt;
    return;
}

int query(int i, int j, int k, int x, int y, db &cnt) {
    if (x <= i && y >= j) {
        cnt = t[k].cnt;
        return t[k].maxv;
    }
    db cntl = 0, cntr = 0;
    int ql = 0, qr = 0;
    if (x <= M) ql = query(i, M, L, x, y, cntl);
    if (y > M) qr = query(M + 1, j, R, x, y, cntr);
    if (x <= M && ql == max(ql, qr)) cnt += cntl;
    if (y > M && qr == max(ql, qr)) cnt += cntr;
    return max(ql, qr);
}

void solve(int l, int r, int *f, db *g) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    sort(a + l, a + r + 1, cmpt);
    solve(l, mid, f, g);
    sort(a + l, a + mid + 1, cmph);
    sort(a + mid + 1, a + r + 1, cmph);
    clear(1, n, 1);
    for (int i = l, j = mid + 1; j <= r; ++j) {
        while (i <= mid && a[i].h >= a[j].h)
            update(1, n, 1, a[i].v, f[a[i].t], g[a[i].t]), ++i;
        db cnt = 0;
        int tmpf = query(1, n, 1, a[j].v, n, cnt);
        if (!tmpf) continue;
        if (f[a[j].t] < tmpf + 1) f[a[j].t] = tmpf + 1, g[a[j].t] = 0;
        if (f[a[j].t] == tmpf + 1) g[a[j].t] += cnt;
    }
    solve(mid + 1, r, f, g);
    return;
}

int main() {
    read(n);
    int maxh = 0;
    FOR(i, 1, n) read(a[i].h, a[i].v), v0[i] = a[i].v, a[i].t = i, chkmax(maxh, a[i].h);
    sort(v0 + 1, v0 + n + 1);
    int tot = unique(v0 + 1, v0 + n + 1) - v0 - 1;
    FOR(i, 1, n) a[i].v = lower_bound(v0 + 1, v0 + tot + 1, a[i].v) - v0;
    FOR(i, 1, n) f1[i] = f2[i] = 1, g1[i] = g2[i] = 1.0;
    solve(1, n, f1, g1);
    int maxx = 0;
    FOR(i, 1, n) chkmax(maxx, f1[i]);
    printf("%d\n", maxx);
    FOR(i, 1, n) if (maxx == f1[i]) sum += g1[i];
    FOR(i, 1, n) a[i].t = n - a[i].t + 1, a[i].h = maxh - a[i].h + 1, a[i].v = n - a[i].v + 1;
    sort(a + 1, a + n + 1, cmpt);
    solve(1, n, f2, g2);
    FOR(i, 1, n) {
        if (f1[i] + f2[n - i + 1] - 1 != maxx) printf("%.5lf ", 0.0);
        else printf("%.5lf ", g1[i] * g2[n - i + 1] / sum);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
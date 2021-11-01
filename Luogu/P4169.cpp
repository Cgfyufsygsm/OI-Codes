#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define lowbit(x) (x & -x)

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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 3e5 + 5, maxx = 1e6 + 5, INF = 1e9;

struct node {
    int x, y, t, op;
} q[maxn << 1], a[maxn << 1], tmp[maxn << 1];
int n, m, tot, ans[maxn << 1], t[maxx << 1];

void insert(int x, int val) {
    for (; x < maxx; x += lowbit(x)) chkmax(t[x], val);
    return;
}

void clear(int x) {
    for (; x < maxx; x += lowbit(x)) t[x] = -INF;
    return;
}

int query(int x) {
    int ret = -INF;
    for (; x; x -= lowbit(x)) chkmax(ret, t[x]);
    return ret;
}

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int i, j, k = l;
    for (i = l, j = mid + 1; j <= r;) {
        while (q[i].x <= q[j].x && i <= mid) {
            if (q[i].op == 1) insert(q[i].y, q[i].x + q[i].y);
            tmp[k++] = q[i++];
        }
        if (q[j].op == 2) chkmin(ans[q[j].t], q[j].x + q[j].y - query(q[j].y));
        tmp[k++] = q[j++];
    }
    for (j = l; j < i; ++j) clear(q[j].y);
    while (i <= mid) tmp[k++] = q[i++];
    FOR(i, l, r) q[i] = tmp[i];
    return;
}

int main() {
    read(n), read(m);
    FOR(i, 1, n) {
        ++tot, read(q[tot].x), read(q[tot].y);
        ++q[tot].x, ++q[tot].y, q[tot].t = 0, q[tot].op = 1;
        ans[tot] = INF;
    }
    FOR(i, 1, m) {
        ++tot, read(q[tot].op), read(q[tot].x), read(q[tot].y);
        ++q[tot].x, ++q[tot].y, q[tot].t = i;
        ans[tot] = INF;
    }

    FOR(i, 0, maxx - 1) t[i] = -INF;

    FOR(i, 1, tot) a[i] = q[i];
    solve(1, tot);

    FOR(i, 1, tot) q[i] = a[i], q[i].x = maxx - a[i].y, q[i].y = a[i].x;
    solve(1, tot);

    FOR(i, 1, tot) q[i] = a[i], q[i].x = maxx - a[i].x, q[i].y = maxx - a[i].y;
    solve(1, tot);

    FOR(i, 1, tot) q[i] = a[i], q[i].x = a[i].y, q[i].y = maxx - a[i].x;
    solve(1, tot);

    FOR(i, 1, tot) if (ans[i] != INF) print(ans[i], '\n');
    return output(), 0;
}
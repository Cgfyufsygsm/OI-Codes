#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int maxn = 1e5 + 5, maxk = 2e5 + 5;

struct node {
    int a, b, c;
    int cnt, ans;
    il friend bool operator!=(const node &a, const node &b) {
        return a.a != b.a || a.b != b.b || a.c != b.c;
    }
} a0[maxn], a[maxn], tmp[maxn];

il bool cmp1(const node &a, const node &b) {
    return a.a == b.a ? (a.b == b.b ? a.c < b.c : a.b < b.b) : a.a < b.a;
}

il bool cmp2(const node &a, const node &b) {
    return a.b == b.b ? a.c < b.c : a.b < b.b;
}

int n, m, k, t[maxk], ans[maxn];

void add(int x, int v) {
    for (; x <= k; x += lowbit(x)) t[x] += v;
    return;
}

int query(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) ret += t[x];
    return ret;
}

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int i, j, k = l;
    for (i = l, j = mid + 1; j <= r;) {
        while (a[j].b >= a[i].b && i <= mid) {
            add(a[i].c, a[i].cnt);
            tmp[k++] = a[i++];
        }
        a[j].ans += query(a[j].c), tmp[k++] = a[j++];
    }
    for (j = l; j < i; ++j) add(a[j].c, -a[j].cnt);
    while (i <= mid) tmp[k++] = a[i++];
    FOR(i, l, r) a[i] = tmp[i];
    return;
}

int main() {
    read(n), read(k);
    FOR(i, 1, n) read(a0[i].a), read(a0[i].b), read(a0[i].c);
    std::sort(a0 + 1, a0 + n + 1, cmp1);
    int same = 0;
    FOR(i, 1, n) {
        ++same;
        if (a0[i] != a0[i + 1]) {
            a[++m] = a0[i];
            a[m].cnt = same;
            a[m].ans = 0;
            same = 0;
        }
    }
    solve(1, m);
    FOR(i, 1, m) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
    FOR(i, 0, n - 1) print(ans[i], '\n');
    return output(), 0;
}
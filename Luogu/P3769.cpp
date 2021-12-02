#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define lowbit(x) (x & -x)

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

const int maxn = 2e5 + 5;
int n;
struct node {
    int x, y, z, w, cnt, id, ans, ok;
    il bool operator==(const node &b) {return x == b.x && y == b.y && z == b.z && w == b.w;}
} a[maxn], tmp[maxn];
int w0[maxn], pos2[maxn], pos1[maxn];

auto cmpx = [](const node &a, const node &b) {return a.x == b.x ? (a.y == b.y ? (a.z == b.z ? a.w < b.w : a.z < b.z) : a.y < b.y) : a.x < b.x;};
auto cmpy = [](const node &a, const node &b) {return a.y == b.y ? (a.x == b.x ? (a.z == b.z ? a.w < b.w : a.z < b.z) : a.x < b.x) : a.y < b.y;};
auto cmpz = [](const node &a, const node &b) {return a.z < b.z;};

int t[maxn];

void add(int x, int v) {
    for (; x <= n; x += lowbit(x))
        chkmax(t[x], v);
    return;
}

int query(int x) {
    int ans = 0;
    for (; x; x -= lowbit(x))
        chkmax(ans, t[x]);
    return ans;
}

void del(int x) {
    for (; x <= n; x += lowbit(x))
        t[x] = 0;
    return;
}

void solve2(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve2(l, mid);
    sort(a + l, a + mid + 1, cmpz);
    sort(a + mid + 1, a + r + 1, cmpz);
    int i, j;
    for (i = l, j = mid + 1; j <= r; ++j) {
        while (a[i].z <= a[j].z && i <= mid) {
            if (a[i].ok) add(a[i].w, a[i].ans);
            ++i;
        }
        if (!a[j].ok) chkmax(a[j].ans, query(a[j].w) + a[j].cnt);
    }
    for (; i >= l; --i) if (a[i].ok) del(a[i].w);
    FOR(i, l, r) tmp[pos2[a[i].id]] = a[i];
    FOR(i, l, r) a[i] = tmp[i];
    solve2(mid + 1, r);
    return;
}

void solve1(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve1(l, mid);
    FOR(i, l, mid) a[i].ok = 1;
    FOR(i, mid + 1, r) a[i].ok = 0;
    sort(a + l, a + r + 1, cmpy);
    FOR(i, l, r) pos2[a[i].id] = i;
    solve2(l, r);
    FOR(i, l, r) tmp[pos1[a[i].id]] = a[i];
    FOR(i, l, r) a[i] = tmp[i];
    solve1(mid + 1, r);
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i].x, a[i].y, a[i].z, a[i].w), w0[i] = a[i].w, a[i].cnt = 1;
    sort(w0 + 1, w0 + n + 1);
    int tot = unique(w0 + 1, w0 + n + 1) - w0 - 1;
    FOR(i, 1, n) a[i].w = lower_bound(w0 + 1, w0 + tot + 1, a[i].w) - w0;
    int n0 = n; n = 1;
    sort(a + 1, a + n0 + 1, cmpx);
    FOR(i, 2, n0) {
        if (a[i].x != a[n].x || a[i].y != a[n].y || a[i].z != a[n].z || a[i].w != a[n].w)
            a[++n] = a[i];
        else a[n].cnt += a[i].cnt;
    }
    FOR(i, 1, n) a[i].id = i, a[i].ans = a[i].cnt, pos1[a[i].id] = i;
    solve1(1, n);
    int ans = 0;
    FOR(i, 1, n) chkmax(ans, a[i].ans);
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
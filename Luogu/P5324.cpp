#include <cstdio>
#include <cctype>
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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1.5e5 + 5, lim = 4.5e5 + 5;

struct node {
    int minv, cnt, ans, tag;
} t[lim << 2];

int cnt[lim], a[maxn];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushup(int k) {
    t[k].minv = min(t[L].minv, t[R].minv);
    t[k].cnt = (t[L].minv == t[k].minv ? t[L].cnt : 0) + (t[R].minv == t[k].minv ? t[R].cnt : 0);
    t[k].ans = t[L].ans + t[R].ans;
    return;
}

void add(int k, int tag) {
    t[k].minv += tag;
    t[k].ans = (t[k].minv == 0) ? t[k].cnt : 0;
    t[k].tag += tag;
    return;
}

il void pushdown(int k) {
    if (t[k].tag) {
        add(L, t[k].tag), add(R, t[k].tag);
        t[k].tag = 0;
    }
    return;
}

void build(int i, int j, int k) {
    if (i == j) {
        t[k].ans = t[k].cnt = 1;
        t[k].minv = 0;
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    pushup(k);
    return;
}

void add(int i, int j, int k, int x, int y, int v) {
    if (x <= i && y >= j) {
        add(k, v);
        return;
    }
    pushdown(k);
    if (x <= M) add(i, M, L, x, y, v);
    if (y > M) add(M + 1, j, R, x, y, v);
    pushup(k);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].ans;
    pushdown(k);
    int ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

void modify(int x, int c) {
    int tmp = x - cnt[x] + 1 - (c > 0);
    add(1, lim, 1, tmp, tmp, c);
    cnt[x] += c;
    return;
}

int main() {
    int n, m;
    read(n), read(m);
    int pos = 1.5e5 + 1;
    build(1, lim, 1);
    FOR(i, 1, n) read(a[i]), a[i] += pos, modify(a[i], 1);
    while (m--) {
        int p, x; read(p), read(x);
        if (p >= 1 && p <= n) {
            if (a[p] <= pos + n) modify(a[p], -1);
            else --cnt[a[p]];
            a[p] = pos + x;
            if (a[p] <= pos + n) modify(a[p], 1);
            else ++cnt[a[p]];
        } else if (x > 0) {
            int tmp = pos + n;
            if (cnt[tmp]) add(1, lim, 1, tmp - cnt[tmp] + 1, tmp, -1);
            --pos;
        } else {
            ++pos;
            int tmp = pos + n;
            if (cnt[tmp]) add(1, lim, 1, tmp - cnt[tmp] + 1, tmp, 1);
        }
        print(query(1, lim, 1, pos + 1, pos + n), '\n');
    }
    return output(), 0;
}
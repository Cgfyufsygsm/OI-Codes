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
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 2e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll maxf[maxn << 2], minf[maxn << 2], a[maxn], b[maxn], sum[maxn];
int n, q;

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    if (i == j) {
        maxf[k] = minf[k] = sum[i];
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    maxf[k] = max(maxf[L], maxf[R]);
    minf[k] = min(minf[L], minf[R]);
    return;
}

ll query_min(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return minf[k];
    ll ret = INF;
    if (x <= M) ret = min(query_min(i, M, L, x, y), ret);
    if (y > M) ret = min(query_min(M + 1, j, R, x, y), ret);
    return ret;
}

ll query_max(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return maxf[k];
    ll ret = -INF;
    if (x <= M) ret = max(query_max(i, M, L, x, y), ret);
    if (y > M) ret = max(query_max(M + 1, j, R, x, y), ret);
    return ret;
}

int main() {
    read(n), read(q);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]);
    FOR(i, 1, n) sum[i] = sum[i - 1] + (b[i] - a[i]);
    build(1, n, 1);
    while (q--) {
        int l, r; read(l), read(r);
        if (query_min(1, n, 1, l, r) < sum[l - 1] || sum[r] - sum[l - 1]) print(-1, '\n');
        else print(query_max(1, n, 1, l, r) - sum[l - 1], '\n');
    }
    return output(), 0;
}
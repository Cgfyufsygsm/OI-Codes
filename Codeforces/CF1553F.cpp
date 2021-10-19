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
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 3e5 + 5, N = 3e5;
using ll = long long;
int n;
ll ans[maxn], t1[maxn], t2[maxn], t3[maxn], sum[maxn], a[maxn];

void insert(ll t[], int x, ll val) {
    for (; x <= N; x += lowbit(x)) t[x] += val;
    return;
}

ll query(ll t[], int x) {
    if (x <= 0) return 0;
    ll ret = 0;
    for (; x; x -= lowbit(x)) ret += t[x];
    return ret;
}

ll calc1(int k) {
    ll ret = 0;
    for (int l = 1, r = a[k] - 1; r <= N && l <= N; l += a[k], r = min((int)(r + a[k]), N))
        ret += query(t2, r) - query(t2, l - 1) - (l - 1) * (query(t1, r) - query(t1, l - 1));
    return ret;
}

ll calc2(int k) {
    ll ret = (k - 1) * a[k];
    ret -= query(t3, a[k]);
    for (int c = 1; c * a[k] <= N; ++c) {
        int l = c * a[k], r = min((c + 1) * a[k] - 1, (ll)N);
        insert(t3, l, c * a[k]), insert(t3, r + 1, -c * a[k]);
    }
    return ret;
}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) {
        ans[i] = calc1(i) + calc2(i) + ans[i - 1];
        sum[i] = a[i] + sum[i - 1];
        insert(t2, a[i], a[i]);
        insert(t1, a[i], 1);
    }
    FOR(i, 1, n) print(ans[i], ' ');
    return output(), 0;
}
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
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

typedef long long ll;
const int maxn = 2e5 + 5, maxk = 55;
int n, k, p;
int a[maxn], b[maxn];

ll t[maxk][maxn];

ll query(int k, int x) {
    if (!x) return 0;
    ll ret = 0;
    for (; x; x -= lowbit(x)) ret += t[k][x];
    return ret;
}

void add(int k, int x, ll val) {
    if (!x) return;
    for (; x <= n; x += lowbit(x)) t[k][x] += val;
    return;
}

int main() {
    read(n), read(k), read(p);
    FOR(i, 1, n) read(a[i]), read(b[i]), ++a[i];
    ll ans = 0;
    int last = 0;
    FOR(i, 1, n) {
        last = (b[i] <= p ? i : last);
        ans += query(a[i], last == i ? last - 1 : last);
        add(a[i], i, 1);
    }
    print(ans);
    return output(), 0;
}
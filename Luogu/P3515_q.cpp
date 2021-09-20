#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
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

typedef double db;
const int maxn = 5e5 + 5;
int a[maxn], n, q[maxn], head, tail, k[maxn];
db f[maxn], sq[maxn];

template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

il db calc(int i, int j) {return a[j] + sq[i - j];}

int bound(int x, int y) {
    int l = y, r = k[x] ? k[x] : n, mid, ret = r + 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (calc(mid, x) <= calc(mid, y))
            ret = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ret;
}

void solve() {
    memset(k, 0, sizeof k);
    head = 1, tail = 0;
    FOR(i, 1, n) {
        while (head < tail && calc(k[tail - 1], q[tail]) < calc(k[tail - 1], i)) --tail;
        k[tail] = bound(q[tail], i), q[++tail] = i;
        while (head < tail && k[head] <= i) ++head;
        f[i] = max(f[i], calc(i, q[head]));
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) sq[i] = sqrt(i), read(a[i]);
    solve();
    FOR(i, 1, n / 2) swap(a[i], a[n - i + 1]), swap(f[i], f[n - i + 1]);
    solve();
    DEC(i, n, 1) print((int)ceil(f[i]) - a[i]), putchar('\n');
    return output(), 0;
}
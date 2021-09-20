#include <cstdio>
#include <cctype>
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
int a[maxn], n;
db p[maxn], sq[maxn];

template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

void solve(int l, int r, int L, int R) {
    if (l > r) return;
    int mid = (l + r) >> 1, k;
    db mx = 0, tmp;
    for (int j = L; j <= mid && j <= R; ++j)
        if ((tmp = a[j] + sq[mid - j]) > mx) mx = tmp, k = j;
    p[mid] = max(p[mid], mx);
    solve(l, mid - 1, L, k);
    solve(mid + 1, r, k, R);
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) sq[i] = sqrt(i), read(a[i]);
    solve(1, n, 1, n);
    FOR(i, 1, n / 2) swap(a[i], a[n - i + 1]), swap(p[i], p[n - i + 1]);
    solve(1, n, 1, n);
    DEC(i, n, 1) print((int)ceil(p[i]) - a[i]), putchar('\n');
    return output(), 0;
}